//============================================================================
// Name        : main.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : main function
//============================================================================
#include <iostream>
#include <string>
#include <std_lib_facilities.h>
#include "Flight.h"
#include "Sort.h"
#include "MyWindow.h"
#include "ArgumentHandler.h"

using namespace std;

void main(int argc, char** argv)
{
	ArgumentHandler ah(argc, argv);
	string default_path = "";
	try {
		default_path = ah.getPath();
	}
	catch(exception e){
		cout << "Invalid input of argument line";
		return;
	}
	function<bool(Flight&, Flight&)> comparison_func;
	function<string(Flight&)> criteria;
	ah.getFunctions(comparison_func, criteria);
	MyWindow(Point(0, 0), WINDOW_W, WINDOW_H, "Flights", default_path, comparison_func, criteria);
	
}
