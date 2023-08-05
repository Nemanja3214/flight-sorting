//============================================================================
// Name        : Sort.h
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>
#include <functional>
#include "Changes.h"
using namespace std;

// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long num_cmps;
	unsigned long num_iter;
	unsigned long num_moves;
	Changes changes;
	vector<Flight>& data;
	function<bool(Flight&, Flight&)> comparison_func;
	string name;
	
public:
	Sort(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, string name);
	~Sort() {};
	// main entry point
	virtual void sort() = 0;
	// returns number of comparisons
	unsigned long getNumCmps();
	unsigned long getNumMoves();
	unsigned long getNumIter();
	Changes getChanges();
	vector<Flight> getFlights();
	string getName();
	
	// resets the number of comparisons
	void resetNumCmps();
	
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	SelectionSort(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, string name) :Sort(data, comparison_func, name) {};
	~SelectionSort() {};
	// main entry point
	void sort() override;
};



// QuickSort class
class QuickSort : public Sort {
public:
	QuickSort(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, string name) : Sort(data, comparison_func, name) {};
	~QuickSort() {};
	void sort() override;
private:
	void sortRec(vector<Flight>& flights, int low, int high, function<bool(Flight&, Flight&)> comparison_func);
	int partition(vector<Flight>& flights, int low, int high, function<bool(Flight&, Flight&)> comparison_func, vector<int>& current_index_state, int iter);
};



// Merge class
class MergeSort : public Sort
{
public:
	MergeSort(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, string name) :Sort(data, comparison_func, name) {};
	~MergeSort() {};
	// main entry point
	void sort() override;
private:
	void sortRec(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, int start, int end);
	void merge(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, int start, int middle, int end);
};