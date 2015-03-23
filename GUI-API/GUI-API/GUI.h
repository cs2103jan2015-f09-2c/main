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
	string outcome; //feedback prompt
	string display;
	string saveAddress;
	Planner myPlanner;
	Storage* myStorage;

public:

	Logic();
	~Logic();
	void processUserInput(string userInput, string currentView);
	string extractCommand(std::string& userInput);
	void processCommand(string command, string taskDetail, string currentView);
	void processCommandAdd(string taskDetail);
	void processCommandDelete(string taskIndex, string currentView);
	void processCommandEdit(string userInput, string currentView);
	void processCommandClear();
	void processCommandUndo();
	void processCommandSearch(string taskDetail);
	void processCommandLoad(string fileName);
	void processCommandSave(string taskDetail);
	void processCommandHelp();
	void processCommandAll();
	void updateDisplay(string viewType);
	void save(string fileName);
	string displayOutcome();
	string displayContent();
};
