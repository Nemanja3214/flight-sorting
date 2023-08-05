//============================================================================
// Name        : ArgumentHandler.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Handles input arguments
//============================================================================
#include <string>
#include <iostream>
#include <vector>
#include "ArgumentHandler.h"
#include "Flight.h"
#include <functional>
#include "std_lib_facilities.h"

using namespace std;

ArgumentHandler::ArgumentHandler(int argc, char** argv):  argc(argc), argv(argv) {};
ArgumentHandler::ArgumentHandler() : argc(0), argv(nullptr) {};
string ArgumentHandler::getPath() {
	string default_path = "";
	if (argc > 1) {
		default_path = string(argv[1]);
	}
    else {
        error("You haven't inputed default path for input in arguments");
    }
	return default_path;
}

void ArgumentHandler::getFunctions(function<bool(Flight&, Flight&)>& comparison_func, function<string(Flight&)>& criteria) {
    char* criteria_name;
    if(argc > 2) {
        criteria_name = strlwr(argv[2]);
    }
    else{
        criteria_name = new char[10];
    }
    if (strcmp(criteria_name, "destination") == 0) {
        comparison_func = [](Flight a, Flight b) {return a.getDestination() < b.getDestination(); };
        criteria = [](Flight a) {return a.getDestination(); };
    }
    else if (strcmp(criteria_name, "departure") == 0) {
        comparison_func = [](Flight a, Flight b) {return a.getDeparture() < b.getDeparture(); };
        criteria = [](Flight a) {return a.getDeparture(); };
    }
    else if (strcmp(criteria_name, "flightno") == 0) {
        comparison_func = [](Flight a, Flight b) {return a.getFlightNo() < b.getFlightNo(); };
        criteria = [](Flight a) {return a.getFlightNo(); };
    }
    else{
        comparison_func = [](Flight a, Flight b) {return a.getGateNo() < b.getGateNo(); };
        criteria = [](Flight a) {return a.getGateNo(); };
    }
}