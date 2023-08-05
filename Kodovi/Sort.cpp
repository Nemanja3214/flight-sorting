//============================================================================
// Name        : Sort.cpp
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================

#include<vector>
#include "Sort.h"
#include "Flight.h"


using namespace std;

Sort::Sort(vector<Flight>& data, function<bool(Flight&, Flight&)> comparison_func, string name) :
	num_cmps(0), num_iter(0), num_moves(0), data(data), comparison_func(comparison_func), name(name) {
};

/// <summary>
/// swaps places of values of two pointers
/// </summary>
/// <typeparam name="T"> pointer type </typeparam>
/// <param name="f1"> pointer 1</param>
/// <param name="f2"> pointer 2</param>
template<typename T>
void change_places(T* f1, T* f2) {
	T temp = *f1;
	*f1 = *f2;
	*f2 = temp;
}

/// <summary>
/// initializes vector of integers were each element is equal to its position in vector
/// </summary>
/// <param name="size"></param>
/// <returns></returns>
vector<int> create_init_change(int size) {
	vector<int> init;
	for (int i = 0; i < size; i++) {
		init.push_back(i);
	}
	return init;
}

/// <summary>
/// sorts vector with selection sort
/// </summary>
void SelectionSort::sort() {
	int min_indx;
	Flight f;
	// 0, 1, 2...
	vector<int> init = create_init_change(this->getFlights().size());
	// current order of indexes compared to previous
	vector<int> current_indexes = vector<int>(init);

	for (int i = 0; i < data.size() - 1; i++) {
		// add changes
		this->changes.addChanges(vector<Flight>(this->data));
		this->changes.addIndexChanges(vector<int>(current_indexes));

		this->changes.addComparisonOfIter(0);
		this->changes.addMovementOfIter(0);

		min_indx = i;
		for (int j = i + 1; j < data.size(); j++) {

			if (comparison_func(data[j], data[min_indx])) {
				min_indx = j;
			}
			num_cmps++;
			this->changes.raiseComparisonOfIter(num_iter);

		}

		//reinitialize vector
		current_indexes.clear();
		current_indexes = vector<int>(init);

		//swap places
		change_places(&data[i], &data[min_indx]);
		change_places(&current_indexes[i], &current_indexes[min_indx]);
		
		num_moves ++;
		this->changes.raiseMovementOfIter(num_iter, 1);
		num_iter++;
		

		
	}
	this->changes.addChanges(vector<Flight>(this->data));
	this->changes.addIndexChanges(vector<int>(current_indexes));
	num_iter++;
}

/// <summary>
/// places all elements lower than the pivot to the left and all higher elements to the right and pivot in between them
/// </summary>
/// <param name="flights"> vector to be sorted</param>
/// <param name="low"> left boundary </param>
/// <param name="high"> right boundary </param>
/// <param name="comparison_func"> lambda function for comparing two flight elements </param>
/// <returns> index next to pivot after placement </returns>
int QuickSort::partition(vector<Flight>& flights, int low, int high, function<bool(Flight&, Flight&)> comparison_func, vector<int>& current_index_state, int iter)
{
	// pivot is always last element
	Flight pivot = flights[high];

	// we start at low
	// i represents right position so far
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		if (comparison_func(flights[j], pivot))
		{
			i++;
			change_places(&flights[i], &flights[j]);
			change_places(&current_index_state[i], &current_index_state[j]);
			num_moves++;

			this->changes.raiseMovementOfIter(iter, 1);
		}
		num_cmps++;
		this->changes.raiseComparisonOfIter(iter);
	}
	change_places(&flights[i + 1], &flights[high]);
	change_places(&current_index_state[i + 1], &current_index_state[high]);


	this->changes.raiseMovementOfIter(iter, 1);
	num_moves++;

	return (i + 1);
}

/// <summary>
/// call function for recursion
/// </summary>
void QuickSort::sort() {
	// current state of indexes compared to previous
	vector<int> current_index_state = create_init_change(this->data.size());
	sortRec(data, 0, data.size()-1, comparison_func);
	this->changes.addChanges(vector<Flight>(this->data));
	this->changes.addIndexChanges(vector<int>(current_index_state));
	num_iter++;
}

/// <summary>
/// recursion function itself, selects pivot and places all lower elements to the left and higher to the right
/// </summary>
/// <param name="flights"> data to be sorted</param>
/// <param name="low"> left boundary </param>
/// <param name="high"> right boundary </param>
/// <param name="comparison_func"> lambda function for comparing two flight elements </param>
void QuickSort::sortRec(vector<Flight>& flights, int low, int high, function<bool(Flight&, Flight&)> comparison_func)
{
	
	if (low < high)
	{
		
		this->changes.addComparisonOfIter(0);
		this->changes.addMovementOfIter(0);
		vector<int> current_index_state = create_init_change(this->getFlights().size());

		//next index after pivot
		int pi = partition(flights, low, high, comparison_func, current_index_state, num_iter);

		num_iter++;

		// remember changes
		this->changes.addChanges(vector<Flight>(this->getFlights()));
		this->changes.addIndexChanges(vector<int>(current_index_state));

		
		sortRec(flights, low, pi - 1, comparison_func);
		sortRec(flights, pi + 1, high, comparison_func);	
	}
	
}

//getters
unsigned long Sort::getNumCmps() { return this->num_cmps; };
unsigned long Sort::getNumMoves() { return this->num_moves; };
unsigned long Sort::getNumIter() { return this->num_iter; };
Changes Sort::getChanges() { return changes; };
string Sort::getName() { return this->name; };
vector<Flight> Sort::getFlights() {return this->data;}