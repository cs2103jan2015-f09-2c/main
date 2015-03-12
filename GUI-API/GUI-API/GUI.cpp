#include "GUI.h"

Planner myPlanner;
GUI::GUI(){
}

GUI::~GUI(){
}

void GUI::processUserInput(string userInput, string currentView) {

	string command = extractCommand(userInput);
	processCommand(command, userInput, currentView);

	updateDisplay(currentView);
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
		//processCommandSave(taskDetail);
	}
	else
	if (command == "help"){
		processCommandHelp();
	}
	else
	if (command == "all"){
		processCommandAll();
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
	outcome = myPlanner.addTask(currentTask);
}

void GUI::processCommandDelete(string taskIndex, string currentView){
	int index = stoi(taskIndex);
	outcome = myPlanner.deleteTask(index, currentView);
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
	outcome = myPlanner.editTask(taskIndex, currentView, taskDetails);
}

void GUI::processCommandClear(){
	outcome = myPlanner.clear();
}

void GUI::processCommandUndo(){
	outcome = myPlanner.undo();
}

void GUI::processCommandSearch(string taskDetail){
	myPlanner.generateSearchList(taskDetail);
	display = myPlanner.toString("search");
}

void GUI::processCommandHelp(){
	string helpMessage = "HELP HELP HELP";
	display = helpMessage;
}

void GUI::processCommandAll(){
	display = myPlanner.AllToString();
}

void GUI::updateDisplay(string viewType) {
	if (viewType == "Help" || viewType == "All"){
		return;
	}

	display = myPlanner.toString(viewType);
}

void GUI::save(string fileName){
	myPlanner.save(fileName);
}

string GUI::displayOutcome(){
	return outcome;
}

string GUI::displayContent(){
	return display;
}