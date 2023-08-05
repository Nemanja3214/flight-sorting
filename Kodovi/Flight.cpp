//============================================================================
// Name        : Flight.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Class that describes flights
//============================================================================
#include <iostream>
#include <string>
#include <std_lib_facilities.h>
#include "Flight.h"
#include <vector>
using namespace std;

/// <summary>
/// splits line by delimiter ;
/// </summary>
/// <param name="line"> string to be separated </param>
/// <returns></returns>
vector<string> tokenize(string line) {
	vector<string> tokens;
	string word;
	stringstream str(line);
	while (getline(str, word, ';'))
		tokens.push_back(word);
	return tokens;
}

/// <summary>
/// loads vector of flight objects
/// </summary>
/// <param name="path"> path to input file </param>
/// <param name="flights"> vector to be loaded, passed by reference </param>
void Flight::load_flights(string path, vector<Flight>& flights) {
	ifstream in_file(path, ios::in);
	if (!in_file) error("can’t open input file ", path);
	Flight f;
	string line;
	getline(in_file, line);
	line.clear();
	while (getline(in_file, line))
		flights.push_back(Flight(tokenize(line)));
	in_file.close();
}

Flight::Flight(string flightNo, string destination, string departure, string gateNo) :
	flightNo(flightNo), destination(destination), departure(departure), gateNo(gateNo) {};

istream& operator>>(istream& in, Flight& f) {
	in >> f.destination >> f.departure >> f.flightNo >> f.gateNo;
	return in;
}

ostream& operator<<(ostream& out, Flight& f) {
	out << f.destination << "; " << f.departure << "; " << f.flightNo << "; " << f.gateNo << "; ";
	return out;
}


Flight::Flight(vector<string> values) :destination(values[0]), departure(values[1]), flightNo(values[2]), gateNo(values[3]) {};

string Flight::getDestination() {
	return this->destination;
}

string Flight::getFlightNo() {
	return this->flightNo;
}

string Flight::getDeparture() {
	return this->departure;
}

string Flight::getGateNo() {
	return this->gateNo;
}
