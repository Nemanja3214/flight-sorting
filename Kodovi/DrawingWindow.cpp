//============================================================================
// Name        : DrawingWindows.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Window class that visualises sorting
//============================================================================

#include "DrawingWindow.h"
#include "Sort.h"

/// <summary>
/// sets output boxes and dots
/// </summary>
/// <param name="cols"> width of matrix</param>
/// <param name="flights_start"> flights at begining of sorting </param>
/// <param name="flights_end"> flights at the end of sorting</param>
/// <param name="outs"> output boxes for writing criterias</param>
/// <param name="dots"> connection of dots represents visualisation</param>
/// <param name="criteria"> with which criteria was vector sorted</param>
void add_components(int cols, vector<Flight>& const flights_start, vector<Flight>& const flights_end, vector<Out_box*>& outs, vector<Circle*>& dots, function<string(Flight&)> criteria) {
    for (int i = 0; i < flights_start.size(); i++) {
        Out_box *o = new Out_box(Point(OUT_X_START, i * OUT_Y_OFFSET), 0, 40, criteria(flights_start[i]));
        outs.push_back(o);
    }
    int i, j;
    for (int k = 0; k < flights_start.size() * cols; k++) {
        i = k / cols;
        j = k % cols;
        dots.push_back(new Circle(Point(OUT_X_START  + j * 30, OUT_Y_START + i * OUT_Y_OFFSET - 20), 3));
        dots[k]->set_color(Color::black);
        dots[k]->draw();
    }
    for (i = 0; i < flights_end.size(); i++) {
        Out_box* o = new Out_box(Point(OUT_X_START + 200 + j * 30, i * OUT_Y_OFFSET), 0, 40, criteria(flights_end[i]));
        outs.push_back(o);
    }
}
/// <summary>
/// connects two dots with a line and attaches it to window
/// </summary>
/// <param name="a"> first dot</param>
/// <param name="b"> second dot</param>
void DrawingWindow::connect_dots(Circle& const a, Circle& const b) {
    Line* l = new Line(a.center(), b.center());
    this->lines.push_back(l);
    attach(*l);
}

/// <summary>
/// gets dot from matrix
/// </summary>
/// <param name="i"> row </param>
/// <param name="j"> column </param>
/// <param name="w"> width of matrix </param>
/// <returns></returns>
Circle* DrawingWindow::getDotAt(int i, int j, int w) {
    return this->dots[i * w + j];
}
//------------------------------------------------------------------------------


DrawingWindow::DrawingWindow(Point xy, int w, int h, const string& title, Sort* sort_alg, function<string(Flight&)> criteria) :
    Window(xy, w, h, title),
    flights((*sort_alg).getFlights()),
    next_button(Point(x_max()/2 - 100, y_max() - 200), 70, 20, "Next", cb_next),
    exit_button(Point(x_max()/2 + 100, y_max() - 200), 70, 20, "Exit", cb_exit),
    button_pushed(false),
    sort_alg(sort_alg),
    iteration_counter(1)
{
    attach(next_button);
    attach(exit_button);
    add_components(sort_alg->getNumIter(), sort_alg->getChanges().getChanges()[0],
        sort_alg->getChanges().getChanges().back(), outs, dots, criteria);
    for (Circle* c : dots) {
        attach(*c);
    }
    for (Out_box* o : outs) {
        attach(*o);
    }    
    wait_for_button();
}

//------------------------------------------------------------------------------

bool DrawingWindow::wait_for_button()
{
    show();
    button_pushed = false;
#if 1
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    Fl::run();
#endif
    return button_pushed;
}

void DrawingWindow::cb_exit(Address, Address pw)
{
    reference_to<DrawingWindow>(pw).exit();
}

//------------------------------------------------------------------------------

void DrawingWindow::cb_next(Address, Address pw)
{
    reference_to<DrawingWindow>(pw).next();
}

//------------------------------------------------------------------------------

/// <summary>
/// increments iteration counter and adds new lines for visualisation
/// </summary>
void DrawingWindow::next()
{
    int j = iteration_counter, dot_i_old;
    if (j < sort_alg->getChanges().getIndexChanges().size()) {

        vector<int> change = sort_alg->getChanges().getIndexChanges().at(j);
        for (int i = 0; i < flights.size(); i++) {
            dot_i_old = change[i];
            connect_dots(*getDotAt(dot_i_old, j - 1, sort_alg->getNumIter()), *getDotAt(i, j, sort_alg->getNumIter()));
        }
        iteration_counter++;
    }
    
    redraw();
}
void DrawingWindow::exit()
{
    button_pushed = true;
    hide();
}

DrawingWindow::~DrawingWindow() {
    for (Out_box* o : this->outs) {
        delete o;
    }
    for (Circle* c : this->dots) {
        delete c;
    }
}
