#include <stdexcept>
#include "GUI.h"
#include "Storage.h"
#include "assert.h"

const string STATUS_MESSAGE_CURRENT_SAVE_ADDRESS = "Tasks will be saved to this address: ";
const string STATUS_MESSAGE_NEW_SAVE_ADDRESS = "Change save address by typing save followed by file address";
const string ERROR_MESSAGE_EMPTY_INPUT = "There was no input entered! Please enter a command!";
const string ERROR_MESSAGE_INVALID_COMMAND = "Invalid command!";
const string ERROR_MESSAGE_INVALID_SERIAL_NO = "Invalid serial number! Serial number should be a positive integer.";
const string ERROR_MESSAGE_MISSING_COLON = "Colon is missing. Please enter a colon after the serial number";
const string CLEAR_CANCELLED = "Clear cancelled.";
const string HELP_MESSAGE = "Add\tadd entries\r\n\r\nEdit\tedit task contents\r\n\r\nDelete\tdelete tasks\r\n\r\nClear\tclears the entire planner\r\n\r\nUndo\tundo the previous add, edit or delete\r\n\r\nSearch\tsearch for keywords throughout all \ttasks\n";


Logic::Logic(){
	myStorage = Storage::getInstanceOfStorage();
	saveAddress = myStorage->retrieveSaveAddress();
	outcome = STATUS_MESSAGE_CURRENT_SAVE_ADDRESS + saveAddress + "\n" + STATUS_MESSAGE_NEW_SAVE_ADDRESS;
	string allTasks = myStorage->load();
	myPlanner.loadData(allTasks);
}

Logic::~Logic(){
}

void Logic::processUserInput(string userInput, string currentView) {
	//Check whether currentView is empty or invalid views 
	assert(currentView == "Done" || currentView == "Home" || currentView == "Missed" || currentView == "Upcoming" || currentView == "Help" || currentView == "All" || currentView == "Search");

	try {
		if (userInput == ""){
			throw ERROR_MESSAGE_EMPTY_INPUT;
		}

		string command = extractCommand(userInput);

		try {
			processCommand(command, userInput, currentView);
		}
		catch (const string error){
			outcome = error;
		}
	}
	catch (const string error ) {
		outcome = error;
	}

	updateDisplay(currentView);
}

string Logic::extractCommand(string& userInput){
	string command = "";
	string taskDetails = "";
	//extract the first word to be the command 
	if (userInput == "show done" || userInput == "clear" || userInput == "save" || userInput == "help" || userInput == "all" || userInput == "undo"){
		command = userInput;
		userInput = taskDetails;
		return command;
	}
	
	//update userInput
	size_t pos = userInput.find_first_of(" ");
	command = userInput.substr(0, pos);
	userInput.erase(0, pos + 1);
	//string newUserInput = userInput.substr(pos + 1, userInput.size() - pos);
	//userInput = newUserInput;
	return command;
}

void Logic::processCommand(std::string command, std::string taskDetail, string currentView) throw (const string) {
	outcome = "";
	if (command == "load"){
		processCommandLoad(taskDetail);
	}

	else
	if (command == "add"){
			processCommandAdd(taskDetail);
	}

	else
	if (command == "delete"){
		try {
			processCommandDelete(taskDetail, currentView);
		}
		catch (const string error) {
			throw error;
		}
	}

	else
	if (command == "edit"){
		try {
			processCommandEdit(taskDetail, currentView);
		}
		catch (const string error){
			throw error;
		}
	}

	else
	if (command == "Y" || command == "N" || command == "y" || command == "n"){
		processCommandClear(command);
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
	else
	if (command == "all"){
		processCommandAll();
	}
	else
	if (command == "recur"){
		processCommandRecur(taskDetail);
	}
	else
	if (command == "done"){
		processCommandDone(taskDetail, currentView);
	}
	else
	if (command == "show done"){
		processCommandShowDone(currentView);
	}
	else {
		throw ERROR_MESSAGE_INVALID_COMMAND;
	}
	string fileContent = myPlanner.saveDataToString();
	string feedback = myStorage->save(fileContent); //think of a better way to get rid of this feedback
}

void Logic::processCommandLoad(string saveAddress){
	string allTasks;
	outcome = myStorage->load(saveAddress, allTasks);

	if (allTasks.empty()){
		return;
	}

	myPlanner.loadData(allTasks);
}

void Logic::processCommandSave(string taskDetail) {
	string fileContent = myPlanner.saveDataToString();
	if (!taskDetail.empty()){
		saveAddress = taskDetail; // need to check whether the save address entered by user is valid
		outcome = myStorage->saveWithFileAddress(saveAddress, fileContent);
	}

	else {
		outcome = myStorage->save(fileContent);
	}
}

void Logic::processCommandAdd(string taskDetail){
	Task currentTask;
	currentTask.addDetails(taskDetail);
	outcome = myPlanner.addTask(currentTask);
}

void Logic::processCommandRecur(string taskDetail){

	Task currentTask;
	list<Task> listOfTasks;
	currentTask.recurTask(taskDetail);
	listOfTasks = currentTask.getRecurringTasks();
	list<Task>::iterator iter;
	for (iter = listOfTasks.begin(); iter != listOfTasks.end(); iter++){
		string outcome = myPlanner.addTask((*iter)); //edit this to inform users that recurring tasks added
	}
}

void Logic::processCommandDelete(string taskIndex, string currentView) throw (invalid_argument&) {
	int index = 0;

	try {
		index = stoi(taskIndex);
	}
	catch (invalid_argument& error){
		throw ERROR_MESSAGE_INVALID_SERIAL_NO;
	}
	
	outcome = myPlanner.deleteTask(index, currentView);
}

void Logic::processCommandDone(string taskIndex, string currentView)throw (invalid_argument&) {
	int index = 0;

	try {
		index = stoi(taskIndex);
	}
	catch (invalid_argument& error){
		throw ERROR_MESSAGE_INVALID_SERIAL_NO;
	}

	outcome = myPlanner.markDone(index, currentView);
}

void Logic::processCommandEdit(string userInput, string currentView) throw (bad_cast&) {
	char colon;
	int taskIndex;
	string taskDetails;
	istringstream in(userInput);
	try {
		if (!(in >> taskIndex)){
			throw bad_cast();
		}
	}
	catch (bad_cast& error){
			throw ERROR_MESSAGE_INVALID_SERIAL_NO;
	}

	try {
		if (!(in >> colon)){
			throw bad_cast();
		}
	}
	catch (bad_cast& error){
		throw ERROR_MESSAGE_MISSING_COLON;
	}

	//in >> taskDetails;
	int sizeToSubstr = userInput.size() - 2;
	taskDetails = userInput.substr(2, sizeToSubstr);
	outcome = myPlanner.editTask(taskIndex, currentView, taskDetails);
}

void Logic::processCommandClear(string command){
	if (command == "Y" || command == "y") {
		outcome = myPlanner.clear();
	}
	else {
		outcome = CLEAR_CANCELLED;
	}
}

void Logic::processCommandUndo(){
	outcome = myPlanner.undo();
}

void Logic::processCommandSearch(string taskDetail){
	outcome = myPlanner.generateSearchList(taskDetail);
	display = myPlanner.toString("Search");
}

void Logic::processCommandHelp(){
	display = HELP_MESSAGE;
	outcome = "Help window";												// prompt for help (refactor needed)
}

void Logic::processCommandShowDone(string currentView){
	display = myPlanner.toString(currentView);
	outcome = "Done list";
}

void Logic::processCommandAll(){
	//display = myPlanner.AllToString();
	outcome = "All list";													//prompt for All (refactor needed)
}

void Logic::updateDisplay(string viewType) {
	if (viewType == "Help" || viewType == "All" || viewType == "Search"){
		return;
	}

	display = myPlanner.toString(viewType);
}

/*void Logic::save(string fileName){
	myPlanner.save(fileName);
} */

string Logic::displayOutcome(){
	return outcome;
}

string Logic::displayContent(){
	return display;
}