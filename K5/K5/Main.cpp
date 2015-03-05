#include "Planner.h"
#include "Task.h"
#include<iostream>
#include <sstream>
#include<string>
#include<list>
#include <ctime>


using namespace std;
string currentView;
Planner myPlanner;
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
		istringstream in(userInput);
		in >> taskIndex;
		in >> colon;
		in >> taskDetails;
		myPlanner.editTask(taskIndex, currentView, taskDetails);
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
		return command;							//hardcoded
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

		std::string command = extractCommand(userInput);
		processCommand(command, userInput);

		std::string display = myPlanner.toString(currentView);
		return display;
	}




	string switchView(string viewType) {
		std::string display = myPlanner.toString(viewType);
		return display;
	}

	int main(){
		string userInput = "add meeting today";
		string command = extractCommand(userInput);
		cout << command << endl;
		cout << userInput << endl;
		system("pause");
		return 0;
	}

/*int main(){
	Task T1, T2, T3, T4, T5, T6, T7;
	Planner P;
	T1.addDetails("meeting school; date 020415 to 020415; time 1500 to 1630 #impt");
	T2.addDetails("go office; date 010115 to 010115; time 1800 to 1830");
	T3.addDetails("do homework; date 150415 to 170415; time 1900 to 1930 #impt");   // this is super weird. dunno why this task cannot add!
	T4.addDetails("meet friends; date 230215 to 230215; time 1500 to 1630");
	T5.addDetails("meet friends; date 230215 to 230215; time 900 to 1000");
	T6.addDetails("meet friends; date 230215 to 230215; time 1800 to 1930");
	T7.addDetails("submit CS homework; date 010115 to 010115; time 1700 to 1730");
	cout << "Added 7 Tasks: " << endl;
	P.addTask(T1);
	P.addTask(T2);
	P.addTask(T3);
	P.addTask(T4);
	P.addTask(T5);
	P.addTask(T6);
	P.addTask(T7);
	cout<<P.toString("allTaskList");
	cout << endl;
	cout << "after deleting number 2: " << endl;
	P.deleteTask(2,"allTaskList");
	cout << P.toString("allTaskList");
	cout << endl;
	cout << "after undoing delete: " << endl;
	P.undo();
	cout << P.toString("allTaskList");
	Task T8;
	T8.addDetails("dentist appointment; date 140215 to 140215; time 1100 to 1115");
	P.addTask(T8);
	cout << endl;
	cout << "Added Task 8: " << endl;
	cout << P.toString("allTaskList");
	P.undo();
	cout << endl;
	cout << "after undoing add: " << endl;
	cout << P.toString("allTaskList");
	P.editTask(5, "allTaskList", "meet girlfriend; date 230215 to 230215; time 1800 to 1930");
	cout << endl;
	cout << "Edit number 5 : friends to girlfriend: " << endl;
	cout<<P.toString("allTaskList");

	P.clear();
	cout << endl;
	cout << "After clearing the list: " << endl;
	cout << P.toString("allTaskList");

	system("pause");
	return 0;
	} */