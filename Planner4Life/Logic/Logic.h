#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Task.h"
#include "Planner.h" 
#include"Log.h"
#include "Storage.h"

using namespace std;

class Logic{
private:
	string _status;
	string _display;
	string _saveAddress;
	Planner _myPlanner;
	Storage* _myStorage;

	//Functions to handle and extract specific commands
	string extractCommand(string&);
	void processCommand(string, string, string);
	void processCommandAdd(string);
	void processCommandDelete(string, string);
	void processCommandEdit(string, string);
	void processCommandClear(string);
	void processCommandUndo();
	void processCommandSearch(string);
	void processCommandLoad(string);
	void processCommandSave(string);
	void processCommandHelp();
	void processCommandAll();
	void processCommandRecur(string);
	void processCommandDone(string, string);
	void processCommandShowDone(string);

public:
	Logic();
	~Logic();

	//Functions to process user input
	void processUserInput(string, string);

	//Functions that updates and returns status and planner content strings
	void updateDisplay(string);
	string displayStatus();
	string displayContent();

	//Functions to check if any tasks have been missed
	bool checkMissedStatus();
};
