#include "GUI.h"

Planner myPlanner;
GUI::GUI(){
}

GUI::~GUI(){
}

string GUI::processUserInput(string userInput, string currentView) {

	string command = extractCommand(userInput);
	processCommand(command, userInput, currentView);

	string display = updateDisplay(currentView);
	return display;
}

string GUI::extractCommand(string& userInput){
	//extract the first word to be the command 
	string command;
	string taskDetails;
	istringstream in(userInput);
	in >> command;
	
	//update userInput
	size_t pos = userInput.find_first_of(" ");
	string newUserInput = userInput.substr(pos + 1, userInput.size() - pos);
	userInput = newUserInput;
	return command;					
}

void GUI::processCommand(std::string command, std::string taskDetail, string currentView){
	if (command == "load"){
		processCommandLoad(taskDetail);
	}

	else
	if (command == "add"){
		processCommandAdd(taskDetail);
	}

	else
	if (command == "delete"){
		processCommandDelete(taskDetail, currentView);
	}

	else
	if (command == "edit"){
		processCommandEdit(taskDetail, currentView);
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
	if (command == "undo"){
		processCommandUndo();
	}
	else
	if (command == "save") {
		processCommandSave(taskDetail);
	}
	else
	if (command == "help"){
		processCommandHelp();
	}

	//save after each operation
	string fileName = "myFile.txt";
	save(fileName);
}

void GUI::processCommandLoad(string fileName){

}

void GUI::processCommandSave(string fileName) {
	save(fileName);
}

void GUI::processCommandAdd(string taskDetail){
	Task currentTask;
	currentTask.addDetails(taskDetail);
	myPlanner.addTask(currentTask);
}

void GUI::processCommandDelete(string taskIndex, string currentView){
	int index = stoi(taskIndex);
	myPlanner.deleteTask(index, currentView);
}

void GUI::processCommandEdit(string userInput, string currentView){
	char colon;
	int taskIndex;
	string taskDetails;
	istringstream in(userInput);
	in >> taskIndex;
	in >> colon;
	//in >> taskDetails;
	int sizeToSubstr = userInput.size() - 2;
	taskDetails = userInput.substr(2, sizeToSubstr);
	myPlanner.editTask(taskIndex, currentView, taskDetails);
}

void GUI::processCommandClear(){
	myPlanner.clear();
}

void GUI::processCommandUndo(){
	myPlanner.undo();
}

void GUI::processCommandSearch(string taskDetail){
	myPlanner.generateSearchList(taskDetail);
}

string GUI::updateDisplay(string viewType) {
	std::string display = myPlanner.toString(viewType);
	return display;
}

void GUI::save(string fileName){
	myPlanner.save(fileName);
}

string GUI::displayHelp() {

	return "HELP HELP HELP";
}