//============================================================================
// Name        : Flight.h
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Class that describes flights
//============================================================================
#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;


class Flight
{
public:
	Flight() {};
	Flight(string flightNo, string destination, string departure, string gateNo);
	Flight(vector<string> values);
	friend istream& operator>>(istream& in, Flight& f);
	friend ostream& operator<<(ostream& in, Flight& f);
	string getDestination();
	string getFlightNo();
	string getDeparture();
	string getGateNo();
	static void load_flights(string path, vector<Flight>& flights);
private:
	string flightNo;
	string destination;
	string departure;
	string gateNo;

};

