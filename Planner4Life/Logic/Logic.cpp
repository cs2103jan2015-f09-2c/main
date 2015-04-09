#include <stdexcept>
#include <exception>
#include "Logic.h"
#include "Storage.h"
#include "assert.h"

const char* STATUS_MESSAGE_CURRENT_SAVE_ADDRESS = "Tasks will be saved to this address: ";
const char* STATUS_MESSAGE_NEW_SAVE_ADDRESS = "Change save address by typing save followed by file address";
const char* ERROR_MESSAGE_INVALID_COMMAND = "Invalid command!";
const char* ERROR_MESSAGE_EMPTY_INPUT = "There was no input entered! Please enter a command!";
const char* ERROR_MESSAGE_INVALID_SERIAL_NO = "Invalid serial number! Serial number should be a positive integer.";
const char* ERROR_MESSAGE_MISSING_COLON = "Colon is missing. Please enter a colon after the serial number";
const char* CLEAR_CANCELLED = "Clear cancelled.";
const char* HELP_MESSAGE = "Add\tadd entries\r\n\r\nEdit\tedit task contents\r\n\r\nDelete\tdelete tasks\r\n\r\nClear\tclears the entire planner\r\n\r\nUndo\tundo the previous add, edit or delete\r\n\r\nSearch\tsearch for keywords throughout all \ttasks\n";

const string HOME_VIEW = "Home";
const string MISSED_VIEW = "Missed";
const string UPCOMING_VIEW = "Upcoming";
const string SEARCH_VIEW = "Search";
const string DONE_VIEW = "Done";
const string HELP_VIEW = "Help";
const string ALL_VIEW = "All";

const string COMMAND_ADD = "add";
const string COMMAND_ALL = "all";
const string COMMAND_DELETE = "delete";
const string COMMAND_EDIT = "edit";
const string COMMAND_UNDO = "undo";
const string COMMAND_CLEAR = "clear";
const string COMMAND_SAVE = "save";
const string COMMAND_DONE = "done";
const string COMMAND_SHOW_DONE = "show done";
const string COMMAND_HELP = "help";
const string COMMAND_LOAD = "load";
const string COMMAND_SEARCH = "search";
const string COMMAND_RECUR = "recur";


Logic::Logic(){
	myStorage = Storage::getInstanceOfStorage();
	saveAddress = myStorage->retrieveSaveAddress();
	status = STATUS_MESSAGE_CURRENT_SAVE_ADDRESS + saveAddress + "\n" + STATUS_MESSAGE_NEW_SAVE_ADDRESS;
	
	string allTasks = myStorage->load();
	myPlanner.loadData(allTasks);
}

Logic::~Logic(){
}

void Logic::processUserInput(string userInput, string currentView) {
	//check whether currentView is empty or invalid views 
	assert(currentView == DONE_VIEW || currentView == HOME_VIEW || currentView == MISSED_VIEW || currentView == UPCOMING_VIEW || currentView == HELP_VIEW || currentView == ALL_VIEW || currentView == SEARCH_VIEW);

	try {
		if (userInput == ""){
			throw exception (ERROR_MESSAGE_EMPTY_INPUT);
		}

		string command = extractCommand(userInput);

		try {
			processCommand(command, userInput, currentView);
		}
		catch (exception const &error){
			status = error.what();
		}
	}
	catch (exception const &error) {
		status = error.what();
	}

	updateDisplay(currentView);
}

string Logic::extractCommand(string& userInput){
	string command = "";
	string taskDetails = "";

	//extract the first word to be the command 
	if (userInput == COMMAND_SHOW_DONE || userInput == COMMAND_CLEAR || userInput == COMMAND_SAVE || userInput == COMMAND_HELP|| userInput == COMMAND_ALL || userInput == COMMAND_UNDO){
		command = userInput;
		userInput = taskDetails;
		return command;
	}

	//update userInput
	size_t spacePos = userInput.find_first_of(" ");
	command = userInput.substr(0, spacePos);
	userInput.erase(0, spacePos + 1);
	return command;
}

void Logic::processCommand(std::string command, std::string taskDetail, string currentView) throw (const string) {
	status = "";
	if (command == COMMAND_LOAD){
		processCommandLoad(taskDetail);
	}

	else if (command == COMMAND_ADD){
		try{
			processCommandAdd(taskDetail);
		}
		
		catch (exception const &error) {
				throw;
			}
	}

	else if (command == COMMAND_DELETE){
		try {
			processCommandDelete(taskDetail, currentView);
		}
		
		catch (exception const &error) {
			throw;
		}
	}

	else if (command == COMMAND_EDIT){
		try {
			processCommandEdit(taskDetail, currentView);
		}
					
		catch (exception const &error){
			throw;
		}
	}

	else if (command == COMMAND_CLEAR){
		processCommandClear(taskDetail);
	}

	else if (command == COMMAND_SEARCH){
		processCommandSearch(taskDetail);
	}

	else if (command == COMMAND_UNDO){
		processCommandUndo();
	}
							
	else if (command == COMMAND_SAVE) {
		processCommandSave(taskDetail);
	}
								
	else if (command == COMMAND_HELP){
		processCommandHelp();
	}
									
	else if (command == COMMAND_ALL){
		processCommandAll();
	}
							
    else if (command == COMMAND_RECUR){
		processCommandRecur(taskDetail);
	}
				
	else if (command == COMMAND_DONE){
		processCommandDone(taskDetail, currentView);
	}
												
	else if (command == COMMAND_SHOW_DONE){
		processCommandShowDone(currentView);
	}
													
	else {
		throw exception(ERROR_MESSAGE_INVALID_COMMAND);
	}
	
	//retrieve content to be saved in txt file
	string fileContent = myPlanner.saveDataToString();

	//auto save the content after each operation
	//feedback variable is a dummy variable to store the status of auto save, which is not necessary to be displayed
	string feedback = myStorage->save(fileContent); 
}

void Logic::processCommandLoad(string saveAddress){
	string allTasks;
	status = myStorage->load(saveAddress, allTasks);

	if (allTasks.empty()){
		return;
	}

	myPlanner.loadData(allTasks);
}

void Logic::processCommandSave(string saveAddress) {
	string fileContent = myPlanner.saveDataToString();

	if (!saveAddress.empty()){
		status = myStorage->saveWithFileAddress(saveAddress, fileContent);
	}

	else {
		status = myStorage->save(fileContent);
	}
}

void Logic::processCommandAdd(string taskDetail){
	Task currentTask;
	currentTask.addDetails(taskDetail);

	status = myPlanner.addTask(currentTask);
}

//@author A0111361Y
void Logic::processCommandRecur(string taskDetail){
	Task currentTask;
	list<Task> listOfTasks;
	currentTask.recurTask(taskDetail);
	listOfTasks = currentTask.getRecurringTasks();
	list<Task>::iterator listIter;
	for (listIter = listOfTasks.begin(); listIter != listOfTasks.end(); listIter++){
		string status = myPlanner.addTask((*listIter));
	}
}

void Logic::processCommandDelete(string taskIndex, string currentView) throw (invalid_argument&) {
	int index = 0;

	try {
		index = stoi(taskIndex);
	}

	catch (invalid_argument& error){
		throw exception(ERROR_MESSAGE_INVALID_SERIAL_NO);
	}

	status = myPlanner.deleteTask(index, currentView);
}

void Logic::processCommandDone(string taskIndex, string currentView)throw (invalid_argument&) {
	int index = 0;

	try {
		index = stoi(taskIndex);
	}

	catch (invalid_argument& error){
		throw exception(ERROR_MESSAGE_INVALID_SERIAL_NO);
	}

	status = myPlanner.markDone(index, currentView);
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
		throw exception(ERROR_MESSAGE_INVALID_SERIAL_NO);
	}

	try {
		if (!(in >> colon)){
			throw bad_cast();
		}
	}

	catch (bad_cast& error){
		throw exception(ERROR_MESSAGE_MISSING_COLON);
	}

	int sizeToSubstr = userInput.size() - 2;
	taskDetails = userInput.substr(3, sizeToSubstr);
	status = myPlanner.editTask(taskIndex, currentView, taskDetails);
}

void Logic::processCommandClear(string command){
	if (command == "Y" || command == "y") {
		status = myPlanner.clear();
	}
	else {
		status = CLEAR_CANCELLED;
	}
}

void Logic::processCommandUndo(){
	status = myPlanner.undo();
}

void Logic::processCommandSearch(string taskDetail){
	status = myPlanner.generateSearchList(taskDetail);
	display = myPlanner.toString(SEARCH_VIEW);
}

void Logic::processCommandHelp(){
	display = HELP_MESSAGE;
	status = "Help window";
}

void Logic::processCommandShowDone(string currentView){
	display = myPlanner.toString(currentView);
	status = "Done list";
}

void Logic::processCommandAll(){
	display = myPlanner.AllToString();
	status = "All list";													//prompt for All (refactor needed)
}

void Logic::updateDisplay(string viewType) {
	if (viewType == HELP_VIEW || viewType == ALL_VIEW || viewType == SEARCH_VIEW){
		return;
	}

	display = myPlanner.toString(viewType);
}

string Logic::displayStatus(){
	return status;
}

string Logic::displayContent(){
	return display;
}

//@author A0111314A
//Function checks the Missed list to see if there are any tasks there. If there are, return true. 
bool Logic::checkMissedStatus(){
	bool missedPresent = false;

	if (!myPlanner.isMissedEmpty()){
		missedPresent = true;
	}

	return missedPresent;
}