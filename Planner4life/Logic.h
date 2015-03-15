#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "C:\Users\User\Desktop\CS2103 Project\Planner4life\Task\Task.h"
#include "Planner.h" 


using namespace std;

class GUI{
private:
	string outcome; //feedback prompt
	string display;

public:

	GUI();
	~GUI();
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
	void processCommandSave(string fileName);
	void processCommandHelp();
	void processCommandAll();
	void updateDisplay(string viewType);
	void save(string fileName);
	string displayOutcome();
	string displayContent();
};

