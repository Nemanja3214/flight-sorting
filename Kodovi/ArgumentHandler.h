//============================================================================
// Name        : ArgumentHandler.h
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Handles input arguments
//============================================================================
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include "Flight.h"
using namespace std;


class ArgumentHandler
{
public:
	ArgumentHandler();
	ArgumentHandler(int argc, char** argv);
	~ArgumentHandler() {};
	//returns default path to input folder specified in argument list
	string getPath();
	void getFunctions(function<bool(Flight&, Flight&)>& comparison_func, function<string(Flight&)>& criteria);
private:
	int argc;
	char** argv;

};
