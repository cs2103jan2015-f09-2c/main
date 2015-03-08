#pragma once
#include <iostream>
#include <sstream>
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
	void processCommandAdd(string taskDetail){
		Task currentTask;
		currentTask.addDetails(taskDetail);
		myPlanner.addTask(currentTask);
	}

	void processCommandDelete(string taskIndex){
		int index = stoi(taskIndex);
		myPlanner.deleteTask(index, currentView);
	}

	void processCommandEdit(string userInput){
		char colon;
		int taskIndex;
		string taskDetails;
		istringstream in (userInput);
		in >> taskIndex;
		in >> colon;
		in >> taskDetails;
		myPlanner.editTask(taskIndex, currentView, taskDetails );
	}

	void processCommandClear(){
		myPlanner.clear();
	}

	void processCommandSearch(string taskDetail){

	}

	void processCommandHelp(){

	}

	string extractCommand(std::string& userInput){
		//extract the first word to be the command and update userInput
		string command;
		string taskDetails;
		istringstream in(userInput);
		in >> command;
		size_t pos = userInput.find_first_of(" ");
		string newUserInput = userInput.substr(pos + 1, userInput.size() - pos);
		userInput = newUserInput;
		return command;						//hardcoded
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

//save after each operation
//		save(fileName);
	}

	
	//to process user input. ideally takes in input and pass off to processing function, which will return a new vector. vector then goes through createString now it takes in input and returns input immediately
	std::string processUserInput(std::string userInput) {
		
		std::string command = extractCommand(userInput);
		processCommand(command, userInput);					

	std::string display = myPlanner.toString(currentView);
		return display;		
	}



	
	string switchView(string viewType) {
		std::string display = myPlanner.toString(viewType);
		return display;
	}

	void save(string fileName){
		myPlanner.save(fileName);
	}
};

