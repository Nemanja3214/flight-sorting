//============================================================================
// Name        : MyWindow.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Window class that is used for selection of criteria and algorithm
//============================================================================

#include <iostream>
#include "MyWindow.h"
#include "DrawingWindow.h"
#include "Sort.h"
#include "std_lib_facilities.h"


MyWindow::MyWindow(Point xy, int w, int h, const string& title, string default_path,
    function<bool(Flight&, Flight&)> comparison_func, function<string(Flight&)> criteria)
    : Window(xy, w, h, title),
flights(flights),
default_path(default_path),
comparison_func(comparison_func),
criteria(criteria),
path_in(Point(X_START, Y_START), 300, 40, "Path to input file"),
path_out(Point(X_START, Y_START + Y_OFFSET), 300, 40, "Path to out file"),
alg_choice1(Point(X_START, Y_START + 2 * Y_OFFSET), 90, 50, "Selection", cb_alg_option1),
alg_choice2(Point(X_START + 2 * X_OFFSET, Y_START + 2 * Y_OFFSET), 90, 50, "Quick", cb_alg_option2),

crit_choice1(Point(X_START, Y_START + 3 * Y_OFFSET), 90, 50, "Destination", cb_crit_option1),
crit_choice2(Point(X_START + 2 * X_OFFSET, Y_START + 3 * Y_OFFSET), 90, 50, "Departure", cb_crit_option2),
crit_choice3(Point(X_START + 4 * X_OFFSET, Y_START + 3 * Y_OFFSET), 90, 50, "Flight No.", cb_crit_option3),
crit_choice4(Point(X_START + 6 * X_OFFSET, Y_START + 3 * Y_OFFSET), 90, 50, "Gate No.", cb_crit_option4),
next_button(Point(X_START + 3 * X_OFFSET, Y_START + 4 * Y_OFFSET), 90, 50, "Next", cb_next),

crit1_button_pushed(false),
crit2_button_pushed(false),
crit3_button_pushed(false),
crit4_button_pushed(false),
button_pushed(false)
	
{
	attach(next_button);
    attach(path_in);
    attach(path_out);

    attach(alg_choice1);
    attach(alg_choice2);

    attach(crit_choice1);
    attach(crit_choice2);
    attach(crit_choice3);
    attach(crit_choice4);

    wait_for_button();
}

void MyWindow::cb_next(Address, Address pw)
{
	reference_to<MyWindow>(pw).next();
}

/// <summary>
/// writes changes during sorting to out file
/// </summary>
/// <param name="changes"> vector that defines changes in every iteration </param>
/// <param name="out_path"> path to out file </param>
void write_changes(Sort* const s, string out_path) {
    ofstream file(out_path, ios::out);
    
    for (int i = 0; i < s->getChanges().getChanges().size() - 1; i++) {
        vector<Flight> vec = s->getChanges().getChanges()[i];
        for (Flight f : vec) {
            file << f <<endl;     
        }
        file << "Comparisons = " << s->getChanges().getComparisonsPerIter()[i]
            << " Movements = " << s->getChanges().getMovementsPerIter()[i] << endl;
        file << "------------------------------------------------------------------------------"<<endl;
    }
    file << "Iterations = " << s->getNumIter() << endl << "Comparisons = " << s->getNumCmps() << endl << "Moves = " << s->getNumMoves() << endl;
    file.close();
}

/// <summary>
/// handles input and output and opens window for visualisation
/// </summary>
void MyWindow::next()
{
    flights.clear();

    //gets flights from in file
    string in_path;
    ifstream f(path_in.get_string());
    if(!f.good()) {
        in_path = default_path;
    }
    else {
        in_path = path_in.get_string();
    }
    Flight::load_flights(in_path, flights);


    //sets lambda functions for comparison and getting criteria value
	button_pushed = true;
    if (this->crit1_button_pushed) {
        comparison_func = [](Flight a, Flight b) {return a.getDestination() < b.getDestination(); };
        criteria = [](Flight a) {return a.getDestination(); };
    }
    else if (this->crit2_button_pushed) {
        comparison_func = [](Flight a, Flight b) {return a.getDeparture() < b.getDeparture(); };
        criteria = [](Flight a) {return a.getDeparture(); };
    }
    else if (this->crit3_button_pushed) {
        comparison_func = [](Flight a, Flight b) {return a.getFlightNo() < b.getFlightNo(); };
        criteria = [](Flight a) {return a.getFlightNo(); };
    }
    else if (this->crit4_button_pushed) {
        comparison_func = [](Flight a, Flight b) {return a.getGateNo() < b.getGateNo(); };
        criteria = [](Flight a) {return a.getGateNo(); };
    }

    //sets sorting algorithm
    Sort* s;
    if (this->alg1_button_pushed) {
        s = new SelectionSort(flights, comparison_func, "Selection sort");
    }
    else if (this->alg2_button_pushed)
    {
        s = new QuickSort(flights, comparison_func, "Quick sort");
    }
    else {
        error("Neither algorithm is chosen");
    }
    s->sort();


    //writes results to out file
    string out_path, default_out_path = "../Izlaz/izlaz.txt";
    
    if (path_out.get_string().empty()) {
        out_path = default_out_path; 
    }
    else {

        out_path = path_out.get_string();
        ofstream f_out(path_out.get_string(), ios::out);
        f_out << "Destination Departure Flight No.Gate No.";
        f_out.close();
    }

    write_changes(s, out_path);
    

    //opens visualisation windows
    DrawingWindow(Point(0, 0), WINDOW_W + 300, WINDOW_H, s->getName(), s, criteria);
    delete s;
    }
//------------------------------------------------------------------------------



void MyWindow::cb_alg_option1(Address, Address pw)
{
    reference_to<MyWindow>(pw).alg1_chosen();
}


//rest is setting colors of buttons and boolean values when they are chosen



void MyWindow::alg1_chosen()
{
    alg1_button_pushed = true;
    alg2_button_pushed = false;
    alg_choice1.set_color(20, 20, 160);
    alg_choice2.set_color(0, 0, 0);
    redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_alg_option2(Address, Address pw)
{
    reference_to<MyWindow>(pw).alg2_chosen();
}



void MyWindow::alg2_chosen()
{
    alg1_button_pushed = false;
    alg2_button_pushed = true;
    alg_choice1.set_color(0, 0, 0);
    alg_choice2.set_color(20, 20, 160);
    redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_crit_option1(Address, Address pw)
{
    reference_to<MyWindow>(pw).crit1_chosen();
}



void MyWindow::crit1_chosen()
{
    crit1_button_pushed = true;
    crit2_button_pushed = false;
    crit3_button_pushed = false;
    crit4_button_pushed = false;
    crit_choice1.set_color(20, 20, 160);
    crit_choice2.set_color(0, 0, 0);
    crit_choice3.set_color(0, 0, 0);
    crit_choice4.set_color(0, 0, 0);
    redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_crit_option2(Address, Address pw)
{
    reference_to<MyWindow>(pw).crit2_chosen();
}



void MyWindow::crit2_chosen()
{
    crit1_button_pushed = false;
    crit2_button_pushed = true;
    crit3_button_pushed = false;
    crit4_button_pushed = false;
    crit_choice1.set_color(0, 0, 0);
    crit_choice2.set_color(20, 20, 160);
    crit_choice3.set_color(0, 0, 0);
    crit_choice4.set_color(0, 0, 0);
    redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_crit_option3(Address, Address pw)
{
    reference_to<MyWindow>(pw).crit3_chosen();
}



void MyWindow::crit3_chosen()
{
    crit1_button_pushed = false;
    crit2_button_pushed = false;
    crit3_button_pushed = true;
    crit4_button_pushed = false;
    crit_choice1.set_color(0, 0, 0);
    crit_choice2.set_color(0, 0, 0);
    crit_choice3.set_color(20, 20, 160);
    crit_choice4.set_color(0, 0, 0);
    redraw();
}

//------------------------------------------------------------------------------

void MyWindow::cb_crit_option4(Address, Address pw)
{
    reference_to<MyWindow>(pw).crit4_chosen();
}



void MyWindow::crit4_chosen()
{
    crit1_button_pushed = false;
    crit2_button_pushed = false;
    crit3_button_pushed = false;
    crit4_button_pushed = true;
    crit_choice1.set_color(0, 0, 0);
    crit_choice2.set_color(0, 0, 0);
    crit_choice3.set_color(0, 0, 0);
    crit_choice4.set_color(20, 20, 160);
    redraw();
}

//------------------------------------------------------------------------------

bool MyWindow::wait_for_button()
// modified event loop:
// handle all events (as per default), quit when button_pushed becomes true
// this allows graphics without control inversion
{
    show();
    button_pushed = false;
#if 1
    // Simpler handler
    while (!button_pushed) Fl::wait();
    Fl::redraw();
#else
    // To handle the case where the user presses the X button in the window frame
    // to kill the application, change the condition to 0 to enable this branch.
    Fl::run();
#endif
    return button_pushed;
}

