#pragma once
#include <string>
#include <vector>
#include "Task.h"
#include "Planner.h"

using namespace std;
string currentView;
class GUI
{
public:
	Planner myPlanner;
	GUI(){
	}

	~GUI(){
	}
	void processCommandAdd(std::string taskDetail){
		Task currentTask;
		currentTask.addDetails(taskDetail);
		myPlanner.addTask(currentTask);
	}

	void processCommandDelete(std::string taskIndex){
		int index = stoi(taskIndex);
		myPlanner.getIndexToDelete(index, currentView);
	}

	void processCommandEdit(std::string taskIndex){
		int index = stoi(taskIndex);
		myPlanner.editTask(index);
	}

	void processCommandClear(){
		myPlanner.clear();
	}

	void processCommandSearch(std::string taskDetail){

	}

	void processCommandHelp(){

	}

	std::string extractCommand(std::string& userInput){
		//extract the first word to be the command and update userInput
		std::string command;
		return command;
	}

	void processCommand(std::string command, std::string taskDetail){
		if (command == "add"){
			processCommandAdd(taskDetail);
		}

		else
		if (command == "delete"){
			processCommandDelete(taskDetail);
		}

		else
		if (command == "edit"){
			processCommandEdit(taskDetail);
		}

		else
		if (command == "clear"){
			processCommandClear();
		}

		else
		if (command == "search"){
			processCommandSearch(taskDetail);
		}

		else
		if (command == "help"){
			processCommandHelp();
		}


	/*	else
		if (command == "exit"){
			processCommandExit();
		} */
	}

	
	//to process user input. ideally takes in input and pass off to processing function, which will return a new vector. vector then goes through createString now it takes in input and returns input immediately
	std::string processUserInput(std::string userInput) {
		
		//--functions for pulling content--//
		//--process--//
		//--write to database--//
		
		std::string command = extractCommand(userInput);
		processCommand(command, userInput);

		std::string display = myPlanner.toString(currentView);
		return display;		//temporary for proof of text entered;
	}



	
	string switchView(string viewType) {
		std::string display = myPlanner.toString(viewType);
	}
};

