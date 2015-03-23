#include <stdexcept>
#include "GUI.h"
#include "assert.h"

const string STATUS_MESSAGE_CURRENT_SAVE_ADDRESS = "Your tasks will be saved to this address: ";
const string STATUS_MESSAGE_NEW_SAVE_ADDRESS = "Change save address by typing save followed by file address";
const string ERROR_MESSAGE_EMPTY_INPUT = "There was no input entered! Please enter a command!";
const string ERROR_MESSAGE_INVALID_COMMAND = "Invalid command!";
const string ERROR_MESSAGE_INVALID_SERIAL_NO = "Invalid serial number! Serial number should be a positive integer.";
const string ERROR_MESSAGE_MISSING_COLON = "Colon is missing. Please enter a colon after the serial number";


Logic::Logic(){
	myStorage = Storage::getInstanceOfStorage();
	saveAddress = myStorage->retrieveSaveAddress();

	if (saveAddress == Storage::DEFAULT_FILE_NAME){
		outcome = STATUS_MESSAGE_CURRENT_SAVE_ADDRESS + saveAddress + "\n" + STATUS_MESSAGE_NEW_SAVE_ADDRESS;
	}
}

Logic::~Logic(){
}

void Logic::processUserInput(string userInput, string currentView) {
	//Check whether currentView is empty or invalid views 
	assert(currentView == "Home" || currentView == "Missed" || currentView == "Upcoming" || currentView == "Help" || currentView == "All");

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

void Logic::processCommand(std::string command, std::string taskDetail, string currentView) throw (const string) {

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
									else
										if (command == "all"){
											processCommandAll();
										}
										else {
											throw ERROR_MESSAGE_INVALID_COMMAND;
										}
	//save after each operation
	string fileName = "myFile.txt";
	save(fileName);
}

void Logic::processCommandLoad(string fileName){

}

void Logic::processCommandSave(string taskDetail) {
	if (!taskDetail.empty()){
		saveAddress = taskDetail; // need to check whether the save address entered by user is valid
		outcome = myStorage->save(saveAddress);
	}

	else {
		outcome = myStorage->save();
	}
}

void Logic::processCommandAdd(string taskDetail){
	Task currentTask;
	currentTask.addDetails(taskDetail);
	outcome = myPlanner.addTask(currentTask);
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

void Logic::processCommandClear(){
	outcome = myPlanner.clear();
}

void Logic::processCommandUndo(){
	outcome = myPlanner.undo();
}

void Logic::processCommandSearch(string taskDetail){
	myPlanner.generateSearchList(taskDetail);
	display = myPlanner.toString("search");
}

void Logic::processCommandHelp(){
	string helpMessage = "HELP HELP HELP"; // refactoring needed
	display = helpMessage;
}

void Logic::processCommandAll(){
	display = myPlanner.AllToString();
}

void Logic::updateDisplay(string viewType) {
	if (viewType == "Help" || viewType == "All"){
		return;
	}

	display = myPlanner.toString(viewType);
}

void Logic::save(string fileName){
	myPlanner.save(fileName);
}

string Logic::displayOutcome(){
	return outcome;
}

string Logic::displayContent(){
	return display;
}