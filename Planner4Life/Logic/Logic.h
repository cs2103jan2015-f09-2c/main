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
	string status;
	string display;
	string saveAddress;
	Planner myPlanner;
	Storage* myStorage;

	string extractCommand(std::string&);
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
	void processUserInput(string, string);
	void updateDisplay(string);
	string displayStatus();
	string displayContent();
	bool checkMissedStatus();
};
