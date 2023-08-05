//============================================================================
// Name        : MyWindow.h
// Author      : Nemanja Majstorović
// Date        : 10.01.2022.
// Copyright   :
// Description : Window class that is used for selection of criteria and algorithm
//============================================================================
#include "Window.h"
#include "GUI.h"
#include "DrawingWindow.h"

#define WINDOW_W			800
#define WINDOW_H			800
#define X_OFFSET			50
#define Y_OFFSET			100
#define X_START			200
#define Y_START			200

using namespace Graph_lib;
class MyWindow : public Window {
public:
	MyWindow(Point xy, int w, int h, const string& title, string default_path,
		function<bool(Flight&, Flight&)> comparison_func, function<string(Flight&)> criteria);
	~MyWindow() {};
	bool wait_for_button();
private:
	vector<Flight> flights;
	string default_path;
	function<bool(Flight&, Flight&)> comparison_func;
	function<string(Flight&)> criteria;

	In_box path_in;
	In_box path_out;
	Button next_button;
	bool button_pushed;
	Button alg_choice1;
	Button alg_choice2;

	Button crit_choice1;
	Button crit_choice2;
	Button crit_choice3;
	Button crit_choice4;

	static void cb_next(Address, Address);
	static void cb_alg_option1(Address, Address);
	static void cb_alg_option2(Address, Address);

	static void cb_crit_option1(Address, Address);
	static void cb_crit_option2(Address, Address);
	static void cb_crit_option3(Address, Address);
	static void cb_crit_option4(Address, Address);

	bool alg1_button_pushed;
	bool alg2_button_pushed;

	bool crit1_button_pushed;
	bool crit2_button_pushed;
	bool crit3_button_pushed;
	bool crit4_button_pushed;

	void alg1_chosen();
	void alg2_chosen();

	void crit1_chosen();
	void crit2_chosen();
	void crit3_chosen();
	void crit4_chosen();
	void next();
};