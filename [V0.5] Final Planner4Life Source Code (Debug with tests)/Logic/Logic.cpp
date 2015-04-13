//@author A0115934E

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
const char* HELP_MESSAGE = "Commands and their functions\r\n\r\nadd\tAdd entries\r\n\r\nedit\tEdit task contents\r\n\r\ndelete\tDelete tasks\r\n\r\nclear\tClears the entire planner\r\n\r\nundo\tUndo the previous add, edit or delete\r\n\r\nrecur\tAdd recurring tasks\r\n\r\nsearch\tSearch for keywords throughout all tasks\n";

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
	_myStorage = Storage::getInstanceOfStorage();
	_saveAddress = _myStorage->retrieveSaveAddress();
	_status = STATUS_MESSAGE_CURRENT_SAVE_ADDRESS + _saveAddress + "\n" + STATUS_MESSAGE_NEW_SAVE_ADDRESS;
	
	string allTasks = _myStorage->load();
	_myPlanner.loadData(allTasks);
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
			_status = error.what();
		}
	}
	catch (exception const &error) {
		_status = error.what();
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

void Logic::processCommand(std::string command, std::string taskDetail, string currentView) {
	_status = "";

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
	string fileContent = _myPlanner.saveDataToString();

	//auto save the content after each operation
	//feedback variable is a dummy variable to store the status of auto save, which is not necessary to be displayed
	string feedback = _myStorage->save(fileContent); 
}

void Logic::processCommandLoad(string saveAddress){
	string allTasks;

	_status = _myStorage->load(saveAddress, allTasks);

	if (allTasks.empty()){
		return;
	}

	_myPlanner.loadData(allTasks);
}

void Logic::processCommandSave(string saveAddress) {
	string fileContent = _myPlanner.saveDataToString();

	if (!saveAddress.empty()){
		_status = _myStorage->saveWithFileAddress(saveAddress, fileContent);
	}
	else {
		_status = _myStorage->save(fileContent);
	}
}

void Logic::processCommandAdd(string taskDetail){
	Task currentTask;

	currentTask.addDetails(taskDetail);

	_status = _myPlanner.addTask(currentTask);
}

//@author A0111361Y
void Logic::processCommandRecur(string taskDetail){
	Task currentTask;
	list<Task> listOfRecurringTasks;

	currentTask.recurTask(taskDetail);
	listOfRecurringTasks = currentTask.getRecurringTasks();

	list<Task>::iterator listIter;

	for (listIter = listOfRecurringTasks.begin(); listIter != listOfRecurringTasks.end(); listIter++){
		string status = _myPlanner.addTask((*listIter));
	}
}

//@author A0115934E
void Logic::processCommandDelete(string taskIndex, string currentView) {
	int index = 0;

	try {
		index = stoi(taskIndex);
	}
	catch (invalid_argument& error){
		throw exception(ERROR_MESSAGE_INVALID_SERIAL_NO);
	}

	_status = _myPlanner.deleteTask(index, currentView);
}

void Logic::processCommandDone(string taskIndex, string currentView) {
	int index = 0;

	try {
		index = stoi(taskIndex);
	}
	catch (invalid_argument &error){
		throw exception (ERROR_MESSAGE_INVALID_SERIAL_NO);
	}

	_status = _myPlanner.markDone(index, currentView);
}

void Logic::processCommandEdit(string userInput, string currentView) {
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
		in >> colon;
		if (colon != ':'){
			throw exception(ERROR_MESSAGE_MISSING_COLON);
		}
	}
	catch (exception const& error){
		throw;
	}

	int sizeOfSubstr = userInput.size() - 2;
	taskDetails = userInput.substr(3, sizeOfSubstr);
	_status = _myPlanner.editTask(taskIndex, currentView, taskDetails);
}

void Logic::processCommandClear(string command){
	if (command == "Y" || command == "y") {
		_status = _myPlanner.clear();
	}
	else {
		_status = CLEAR_CANCELLED;
	}
}

void Logic::processCommandUndo(){
	_status = _myPlanner.undo();
}

void Logic::processCommandSearch(string taskDetail){
	_status = _myPlanner.generateSearchList(taskDetail);
	_display = _myPlanner.toString(SEARCH_VIEW);
}

void Logic::processCommandHelp(){
	_display = HELP_MESSAGE;
	_status = HELP_VIEW;
}

void Logic::processCommandShowDone(string currentView){
	_display = _myPlanner.toString(currentView);
	_status = DONE_VIEW;
}

void Logic::processCommandAll(){
	_display = _myPlanner.AllToString();
	_status = ALL_VIEW;
}

void Logic::updateDisplay(string viewType) {
	if (viewType == HELP_VIEW || viewType == ALL_VIEW || viewType == SEARCH_VIEW || viewType == DONE_VIEW){
		return;
	}

	_display = _myPlanner.toString(viewType);
}

string Logic::displayStatus(){
	return _status;
}

string Logic::displayContent(){
	return _display;
}

//@author A0111314A
//Function checks the Missed list to see if there are any tasks there. If there are, return true. 
bool Logic::checkMissedStatus(){
	bool missedPresent = false;

	if (!_myPlanner.isMissedEmpty()){
		missedPresent = true;
	}

	return missedPresent;
}