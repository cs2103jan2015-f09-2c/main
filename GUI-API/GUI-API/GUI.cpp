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
	string outcome;

	if (command == "load"){
		processCommandLoad(taskDetail);
	}

	else
	if (command == "add"){
		outcome = processCommandAdd(taskDetail);
	}

	else
	if (command == "delete"){
		outcome = processCommandDelete(taskDetail, currentView);
	}

	else
	if (command == "edit"){
		outcome = processCommandEdit(taskDetail, currentView);
	}

	else
	if (command == "clear"){
		outcome = processCommandClear();
	}

	else
	if (command == "search"){
		processCommandSearch(taskDetail);
	}

	else
	if (command == "undo"){
		outcome = processCommandUndo();
	}
	else
	if (command == "save") {
		//processCommandSave(taskDetail);
	}
	else
	if (command == "help"){
		string helpMessage;
		processCommandHelp(helpMessage);
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

string GUI::processCommandAdd(string taskDetail){
	Task currentTask;
	currentTask.addDetails(taskDetail);
	string outcome = myPlanner.addTask(currentTask);
	return outcome;
}

string GUI::processCommandDelete(string taskIndex, string currentView){
	int index = stoi(taskIndex);
	string outcome = myPlanner.deleteTask(index, currentView);
	return outcome;
}

string GUI::processCommandEdit(string userInput, string currentView){
	char colon;
	int taskIndex;
	string taskDetails;
	istringstream in(userInput);
	in >> taskIndex;
	in >> colon;
	//in >> taskDetails;
	int sizeToSubstr = userInput.size() - 2;
	taskDetails = userInput.substr(2, sizeToSubstr);
	string outcome = myPlanner.editTask(taskIndex, currentView, taskDetails);
	return outcome;
}

string GUI::processCommandClear(){
	string outcome = myPlanner.clear();
	return outcome;
}

string GUI::processCommandUndo(){
	string outcome = myPlanner.undo();
	return outcome;
}

string GUI::processCommandSearch(string taskDetail){
	string outcome = myPlanner.generateSearchList(taskDetail);
	return outcome;
}

void GUI::processCommandHelp(string& helpMessage){
	helpMessage = "HELP HELP HELP";
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

string displayContent(){

	return outcome;
}