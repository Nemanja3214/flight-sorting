//============================================================================
// Name        : Changes.h
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Receives changes and processes them
//============================================================================
#include <string>
#include <iostream>
#include <vector>
#include "Flight.h"
#include <map>
using namespace std;


class Changes
{
public:
	Changes() {};
	~Changes() {};
	vector<vector<int>> getIndexChanges();
	vector<vector<Flight>> getChanges();
	void addIndexChanges(vector<int> vec);
	void addChanges(vector<Flight> vec);
	vector<int> getComparisonsPerIter();
	vector<int> getMovementsPerIter();
	void addComparisonOfIter(int num);
	void addMovementOfIter(int num);
	void raiseComparisonOfIter(int indx);
	void raiseMovementOfIter(int indx, int num);
private:
	vector<vector<int>> index_changes;
	vector<vector<Flight>> changes;
	vector<int> comparisons_per_iter;
	vector<int> movements_per_iter;

};
