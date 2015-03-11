#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Task.h"
#include "Planner.h" 


using namespace std;

class GUI
{
public:
	
	GUI();
	~GUI();
	string processUserInput(string userInput, string currentView);
	string extractCommand(std::string& userInput);
	void processCommand(string command, string taskDetail, string currentView);
	string processCommandAdd(string taskDetail);
	string processCommandDelete(string taskIndex, string currentView);
	string processCommandEdit(string userInput, string currentView);
	string processCommandClear();
	string processCommandUndo();
	string processCommandSearch(string taskDetail);
	void processCommandLoad(string fileName);
	void processCommandSave(string fileName);
	void processCommandHelp(string& helpMessage);
	string updateDisplay(string viewType);
	void save(string fileName);
	string displayHelp();
};

