//============================================================================
// Name        : Changes.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Receives changes and processes them
//============================================================================

#include "Changes.h"
vector<vector<int>> Changes::getIndexChanges() { return this->index_changes; };
vector<vector<Flight>> Changes::getChanges() { return this->changes; };

void Changes::addIndexChanges(vector<int> vec) {
	this->index_changes.push_back(vec);
}
void Changes::addChanges(vector<Flight> vec) {
	this->changes.push_back(vec);
}

vector<int> Changes::getComparisonsPerIter() {
	return this->comparisons_per_iter;
};
vector<int> Changes::getMovementsPerIter() {
	return this->movements_per_iter;
}
void Changes::addComparisonOfIter(int num) {
	this->comparisons_per_iter.push_back(num);
};
void Changes::addMovementOfIter(int num) {
	this->movements_per_iter.push_back(num);
}

void Changes::raiseComparisonOfIter(int indx) {
	this->comparisons_per_iter.at(indx)++;
};
void Changes::raiseMovementOfIter(int indx, int num) {
	this->movements_per_iter.at(indx)+=num;
}
