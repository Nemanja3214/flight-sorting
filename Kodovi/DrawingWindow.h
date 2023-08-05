//============================================================================
// Name        : Flight.h
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Window class that visualises sorting
//============================================================================

#ifndef SIMPLE_WINDOW_GUARD
#define SIMPLE_WINDOW_GUARD 1
#define OUT_X_OFFSET			50
#define OUT_Y_OFFSET			40
#define OUT_X_START			100
#define OUT_Y_START			40


#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "Sort.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

class DrawingWindow : public Window{
public:
    DrawingWindow(Point xy, int w, int h, const string& title, Sort* sort_alg, function<string(Flight&)> criteria);
    ~DrawingWindow();

    bool wait_for_button(); // simple event loop


private:
    Button next_button;
    Button exit_button;
    bool button_pushed; 
    Sort* sort_alg;
    vector<Flight> flights;
    vector<Circle*> dots;
    vector<Out_box*> outs;
    vector<Line*> lines;
    int iteration_counter;

    static void cb_next(Address, Address); 
    void next();            
    static void cb_exit(Address, Address); 
    void exit();           
    void connect_dots(Circle& const a, Circle& const b);
    Circle* getDotAt(int i, int j, int w);

};

//------------------------------------------------------------------------------

#endif // SIMPLE_WINDOW_GUARD
