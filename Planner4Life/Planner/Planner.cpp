#include "Planner.h"
#include "Log.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <ctime>
#include <sstream>
#include <fstream>

const string COMMAND_ADD = "add";
const string COMMAND_DELETE = "delete";
const string COMMAND_EDIT = "edit";
const string COMMAND_UNDO = "undo";
const string COMMAND_CLEAR = "clear";
const string COMMAND_SAVE = "save";
const string COMMAND_DONE = "done";

const string HOME_LIST = "Home";
const string MISSED_LIST = "Missed";
const string UPCOMING_LIST = "Upcoming";
const string SEARCH_LIST = "Search";
const string DONE_LIST = "Done";

const string SEARCH_RESULTS_MSG = "Search Results";

const string LOG_FILE_UPDATE_KEY_WORD = "UPDATE";
const string LOG_FILE_ADD_TASK_INTRO_MSG = "ID of new entry is ";
const string LOG_FILE_DELETE_TASK_INTRO_MSG = "ID of deleted entry is ";
const string LOG_FILE_CLEAR_TASK_MSG = "Delete ID : ";
const string LOG_FILE_EDIT_TASK_MSG = "Edit Taken Place ";
const string LOG_FILE_SAVE_MSG = "File Save Operation";
const string LOG_FILE_MARK_DONE_MSG = "The item is marked as done";

const string ERROR_MESSAGE_FATAL = "Fatal Error !!";
const string ERROR_MESSSAGE_INVALID_LIST_NAME = "Error!! Name of list is invalid!!";
const string ERROR_MESSSAGE_INVALID_FILE_NAME = "Error!! Name of file is invalid!!";
const string ERROR_MESSSAGE_INVALID_COMMAND = "Error!! Command is invalid!!";
const string ERROR_MESSAGE_INVALID_INDEX = "Invalid index!";
const string ERROR_MESSAGE_INVALID_UNDO = "Nothing to undo!";

const string EMPTY_LIST_MESSAGE = "There are no tasks here";
const string NO_RESULTS_MESSAGE = "No results found!";
const string NEWLINE = "\r\n";
const string IMPORTANCE_SYMBOL = "#impt";
const string DONE_KEYWORD = "DONE";
const string CLASH_KEYWORD = " TASK CLASH !!!";
const string DUPLICATE_STATUS = "duplicate";

const string STATUS_TO_STRING_ADD_INTRO = "Task added: ";
const string STATUS_TO_STRING_DELETE_INTRO = "Task deleted:";
const string STATUS_TO_STRING_EDIT_INTRO = "The following Task : \r\n";
const string STATUS_TO_STRING_EDIT_MID = "\r\nhas been edited to :\r\n";
const string STATUS_TO_STRING_UNDO_ADD_MSG = "The following Task has been added back: \r\n";
const string STATUS_TO_STRING_UNDO_DELETE_MSG = "The following Task has been removed: \r\n";
const string STATUS_TO_STRING_CLEAR_MSG = "All content cleared. \r\n";
const string STATUS_TO_STRING_SAVE_MSG = "File has been saved. \r\n";
const string STATUS_TO_STRING_DONE_MSG = "Task has been marked as done \r\n";
const string STATUS_TO_STRING_DUPLICATE_MSG = "The following Task has a duplicate: ";

const int STARTING_SERIAL_NUMBER = 1;

using namespace std;

/************************************************************************************************

Initialization

************************************************************************************************/
//Public Function
//@author A0111314A
//variable currentDate is initialized to the system date when Planner4Life is opened
Planner::Planner(){
	time_t currentTime = time(0);
	struct tm * now = localtime(&currentTime);			//get local time
	currentDate.year = (now->tm_year - 100);	//last 2 digits of year
	currentDate.month = (now->tm_mon + 1);		//month: jan = 1, feb = 2 etc
	currentDate.day = (now->tm_mday);
}

/************************************************************************************************

Command Functions

************************************************************************************************/
//Public Functions

//@author A0111361Y
//Task is added to the Planner in this function
//Before the actual addition of the task, function checks for:
//duplicates, place to slot in and clashes
//function ends by generating all the other dependent lists
string Planner::addTask(Task newTask){

	//create new task
	int id = getNewId(); // use static to actually create id

	newTask.storeIdNumber(id);

	//check for duplicate
	bool duplicatePresent = false;
	duplicatePresent = isDuplicatePresent(newTask);

	//check where to slot
	list<Task>::iterator iter, iterTwoDate, iterOneDate;
	bool twoDatePresent = false, oneDatePresent = false;


	//case 1: when new task has no date and no time
	if (newTask.getNumOfDates() == 0 && newTask.getNumOfTimes() == 0){
		//look for slot at the end of tasks with no date and no time
		for (iter = All.begin(); iter != All.end(); ++iter){
			if ((*iter).getNumOfDates() > 0 || (*iter).getNumOfTimes() > 0){
				break;
			}
		}
	}

	//case 2: when new task has no date and has time (either 1 or 2 times)
	else if (newTask.getNumOfDates() == 0 && newTask.getNumOfTimes() > 0){
		for (iter = All.begin(); iter != All.end(); ++iter){
			if ((*iter).getTimeStart() > newTask.getTimeStart() || (*iter).getNumOfDates() > 0){
				break;
			}
		}
	}

	//case 3:  when new task has more than one date (0,1 or 2 times)
	else if (newTask.getNumOfDates() >0){
		for (iter = All.begin(); iter != All.end(); ++iter){
			if ((*iter).getDateStart().year > newTask.getDateStart().year){
				break;
			}
			else if ((*iter).getDateStart().year == newTask.getDateStart().year){
				if ((*iter).getDateStart().month > newTask.getDateStart().month){
					break;
				}
				else if ((*iter).getDateStart().month == newTask.getDateStart().month){
					if ((*iter).getDateStart().day > newTask.getDateStart().day){
						break;
					}
					else if ((*iter).getDateStart().day == newTask.getDateStart().day){
						if ((*iter).getTimeStart() > newTask.getTimeStart()){
							break;
						}
						else if ((*iter).getTimeStart() == newTask.getTimeStart()){
							if (((*iter).getTimeEnd() - (*iter).getTimeStart()) > (newTask.getTimeEnd() - newTask.getTimeStart())){
								break;
							}
						}
					}
				}
			}
		}
	}
	//case 4: when new task has 1 date (0,1 or 2 times)
	else if (newTask.getNumOfDates() == 1){
		int numofTimes = newTask.getNumOfTimes();
		int yearS = newTask.getDateStart().year;
		int monthS = newTask.getDateStart().month;
		int dayS = newTask.getDateStart().day;

		for (iter = All.begin(); iter != All.end(); ++iter){
			int IyearE = (*iter).getDateStart().year;
			int ImonthE = (*iter).getDateStart().month;
			int IdayE = (*iter).getDateStart().day;

			if ((*iter).getDateStart().year > newTask.getDateEnd().year){
				break;
			}
			else if ((*iter).getDateStart().year == newTask.getDateEnd().year){
				if ((*iter).getDateStart().month > newTask.getDateStart().month){
					if ((*iter).getDateEnd().year > newTask.getDateEnd().year){
						break;
					}
					else if ((*iter).getDateEnd().year == newTask.getDateEnd().year){
						if ((*iter).getDateEnd().month > newTask.getDateEnd().month){
							break;
						}
						else if ((*iter).getDateEnd().month == newTask.getDateEnd().month){
							if ((*iter).getDateEnd().day > newTask.getDateEnd().day){
								break;
							}
							else if ((*iter).getDateEnd().day == newTask.getDateEnd().day){
								if ((*iter).getTimeStart() > newTask.getTimeStart()){
									break;
								}
								else if ((*iter).getTimeStart() == newTask.getTimeStart()){
									if (((*iter).getTimeEnd() - (*iter).getTimeStart()) > (newTask.getTimeEnd() - newTask.getTimeStart())){
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	All.insert(iter, newTask);

	string status;
	if (duplicatePresent){
		status = statusToString(DUPLICATE_STATUS, newTask);
	}
	else {
		status = statusToString(COMMAND_ADD, newTask);
	}

	updateLastEntryStructure(COMMAND_ADD, newTask);


	checkListForClashes();
	generateAllOtherList();

	//logging
	stringstream message;
	message << LOG_FILE_ADD_TASK_INTRO_MSG << id;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());


	return status;
}

//@author A0111361Y
//The view is taken in with the serial number
//ID number of the task is retrieved using the view and serial number
//Corresponding ID number is then deleted
string Planner::deleteTask(int serialNumber, string nameOfView){
	int idNumber;
	string status;
	list<Task> ::iterator taskIter;
	
	if (nameOfView == HOME_LIST){
		if (indexChecker(taskIter, serialNumber, homeList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*taskIter).getIdNumber();
			status = deleteIndex(idNumber);
		}
	}
	else if (nameOfView == MISSED_LIST){
		if (indexChecker(taskIter, serialNumber, missedList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*taskIter).getIdNumber();
			status = deleteIndex(idNumber);
		}
	}
	else if (nameOfView == UPCOMING_LIST){
		if (indexChecker(taskIter, serialNumber, upcomingList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*taskIter).getIdNumber();
			status = deleteIndex(idNumber);
		}
	}
	else{
		throw ERROR_MESSSAGE_INVALID_LIST_NAME;
	}
	
	//logging
	stringstream message;
	message << LOG_FILE_DELETE_TASK_INTRO_MSG << idNumber;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());

	return status;
}

//@author A0111361Y
//The function checks the lastEntry structure for the command and entry,
//then performs the reverse of the command
string Planner::undo(void){
	string status;
	string command = lastEntry.lastCommand;

	if (command == COMMAND_ADD){
		int lastEntryID = getNewId() - 1;
		deleteIndex(lastEntryID);
	}
	else if (command == COMMAND_DELETE){
		addTask(lastEntry.lastTask);
	}
	else if (command == COMMAND_EDIT){
		deleteIndex(lastEdit.addedTask.getIdNumber());
		addTask(lastEdit.deletedTask);
	}
	else {
		throw ERROR_MESSAGE_INVALID_UNDO;
	}

	status = undoStatusToString();
	checkListForClashes();
	generateAllOtherList();

	return status;
}

//@author A0111361Y
//Clears the All list and generates all other lists
string Planner::clear(void){
	string status;
	
	All.clear();
	generateAllOtherList();
	
	//logging
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, LOG_FILE_CLEAR_TASK_MSG);
	status = clearStatusToString();
	
	return status;
}

//@author A0111361Y
string Planner::editTask(int serialNumber, string nameOfList, string input){
	Task newTask;
	string validEditCheck;
	string status;

	newTask.addDetails(input);
	
	validEditCheck = deleteTask(serialNumber, nameOfList);
	if (validEditCheck == ERROR_MESSAGE_INVALID_INDEX) {
		return ERROR_MESSAGE_INVALID_INDEX;														//UNHANDLED EXCEPTION****************************************************************************
	}
	else {
		lastEdit.deletedTask = lastEntry.lastTask;
		addTask(newTask);
		lastEdit.addedTask = newTask;
		lastEntry.lastCommand = COMMAND_EDIT;

		generateAllOtherList();
		
		//logging
		LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, LOG_FILE_EDIT_TASK_MSG);

		status = editStatusToString();

		return status;
	}
}

//@author A0111361Y
//The view is taken in with the serial number
//ID number of the task is retrieved using the view and serial number
//Corresponding ID number is then marked as done
string Planner::markDone(int serialNumber, string nameOfList){
	int idNumber = 0;
	string status;
	list<Task> ::iterator taskIter;

	if (nameOfList == HOME_LIST){
		if (indexChecker(taskIter, serialNumber, homeList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*taskIter).getIdNumber();
			status = markDoneIndex(idNumber);
		}
	}
	else if (nameOfList == MISSED_LIST){
		if (indexChecker(taskIter, serialNumber, missedList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*taskIter).getIdNumber();
			status = markDoneIndex(idNumber);
		}
	}
	else if (nameOfList == UPCOMING_LIST){
		if (indexChecker(taskIter, serialNumber, upcomingList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*taskIter).getIdNumber();
			status = markDoneIndex(idNumber);
		}
	}
	else{
		throw ERROR_MESSSAGE_INVALID_LIST_NAME;
	}

	//logging
	stringstream message;
	message << LOG_FILE_MARK_DONE_MSG << idNumber;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());

	return status;

}

//@author A0111361Y
//Function takes in the search target
//passes the target to every task and checks if the target is present in the task
//generates a list of all the tasks that return true
string Planner::generateSearchList(string target){
	list<Task> ::iterator taskIter;
	Task targetTask;
	string status;

	searchList.clear();
	for (taskIter = All.begin(); taskIter != All.end(); ++taskIter){
		targetTask = *taskIter;
		if (targetTask.isSearchTargetPresent(target)){
			searchList.push_back(targetTask);
		}
	}

	status = searchStatusToString();

	return status;
}

/************************************************************************************************

Functions that returns Lists in string form

************************************************************************************************/
//Public Functions

//@author A0111361Y
//returns the requested list in string form
string Planner::toString(string nameOfList){
	//convert the list to a string and return
	string displayString;
	if (nameOfList == HOME_LIST){
		displayString = homeListToString();
	}
	else if (nameOfList == UPCOMING_LIST){
		displayString = upcomingListToString();
	}
	else if (nameOfList == MISSED_LIST){
		displayString = missedListToString();
	}
	else if (nameOfList == SEARCH_LIST){
		displayString = searchListToString();
	}
	else if (nameOfList == DONE_LIST){
		displayString = doneListToString();
	}
	else displayString = ERROR_MESSSAGE_INVALID_LIST_NAME;														//UNHANDLED EXCEPTION **********************************************		

	return displayString;
}

//@author A0111361Y
//returns the All list in string form
string Planner::AllToString(void){
	ostringstream out;
	list<Task> ::iterator taskIter;
	string displayString;
	taskIter = All.begin();
	int serialNumber = STARTING_SERIAL_NUMBER;
	
	if (!All.empty()){
		for (taskIter = All.begin(); taskIter != All.end(); ++taskIter){
			out << serialNumber;
			out<< ". ";
			out << descriptionOfTaskToString(*(taskIter));
			out << NEWLINE;
			serialNumber++;
		}
	}
	else {
		out << EMPTY_LIST_MESSAGE << endl;
	}

	displayString = out.str();

	return displayString;
}

/************************************************************************************************

Status Returning Functions

************************************************************************************************/
//Public Functions

//@author A0111361Y
//returns the status after each command is successfully executed
string Planner::statusToString(string command, Task theTask){
	string displayString;
	if (command == COMMAND_ADD){
		displayString = addStatusToString(theTask);
	}
	else if (command == COMMAND_DELETE){
		displayString = deleteStatusToString(theTask);
	}
	else if (command == COMMAND_EDIT){
		displayString = editStatusToString();
	}
	else if (command == COMMAND_UNDO){
		displayString = undoStatusToString();
	}
	else if (command == COMMAND_CLEAR){
		displayString = clearStatusToString();
	}
	else if (command == COMMAND_SAVE){
		displayString = saveStatusToString();
	}
	else if (command == COMMAND_DONE){
		displayString = doneStatusToString();
	}
	else if (command == DUPLICATE_STATUS){
		displayString = duplicateStatusToString(theTask);
	}
	else displayString = ERROR_MESSSAGE_INVALID_COMMAND;										//	UNHANDLED EXCEPTION*********************************************

	return displayString;
}

//@author A0111361Y
//converts and returns all of the tasks in All to input format
string Planner::saveDataToString(){
	ostringstream out;
	list<Task> ::iterator it;
	it = All.begin();

	if (!All.empty()){

		for (it = All.begin(); it != All.end(); ++it){
			out << (*it).getDescription();

			switch ((*it).getNumOfDates()){
			case 0:
				break;
			case 1:
				out << "; date ";
				if ((*it).getDateEnd().day < 10){
					out << "0" << (*it).getDateEnd().day;
				}
				else out << (*it).getDateEnd().day;
				if ((*it).getDateEnd().month < 10){
					out << "0" << (*it).getDateEnd().month;
				}

				if ((*it).getDateEnd().year < 10){
					out << "0" << (*it).getDateEnd().year << " ";
				}
				else out << (*it).getDateEnd().year << " ";
				break;
			case 2:
				out << "; date ";
				if ((*it).getDateStart().day < 10){
					out << "0" << (*it).getDateStart().day;
				}
				else out << (*it).getDateStart().day;
				if ((*it).getDateStart().month < 10){
					out << "0" << (*it).getDateStart().month;
				}

				if ((*it).getDateStart().year < 10){
					out << "0" << (*it).getDateStart().year << " ";
				}
				else out << (*it).getDateStart().year << " ";

				out << " to ";

				if ((*it).getDateEnd().day < 10){
					out << "0" << (*it).getDateEnd().day;
				}
				else out << (*it).getDateEnd().day;
				if ((*it).getDateEnd().month < 10){
					out << "0" << (*it).getDateEnd().month;
				}
				if ((*it).getDateEnd().year < 10){
					out << "0" << (*it).getDateEnd().year << " ";
				}
				else out << (*it).getDateEnd().year << " ";

				break;
			}

			switch ((*it).getNumOfTimes()){
			case 0:
				break;
			case 1:
				out << "; time ";
				out << (*it).getTimeStart();
				break;
			case 2:
				out << "; time ";
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
				break;
			default:
				throw ERROR_MESSAGE_FATAL;
			}


			if ((*it).doneStatus() == true){
				out << DONE_KEYWORD;
			}

			if ((*it).getImportance()){
				out << IMPORTANCE_SYMBOL;
			}

			out << NEWLINE;

		}

	}
	else out << "";

	return out.str();
}

/************************************************************************************************

Load Functions

************************************************************************************************/
//Public Functions

//@author A0111361Y
//reads in all the tasks from the text file
//adds in all the tasks into All
void Planner::loadData(string data){
	Task* loadTaskPtr;
	string extractedSingleLine;
	string doneKeyword = DONE_KEYWORD;
	bool isTaskMarkedAsDone = false;
	size_t start = 0, end = 0;
	
	All.clear();

	while (data.size()>0){
		end = data.find_first_of("\n");
		extractedSingleLine = data.substr(start, end - start);
		if (extractedSingleLine.find(doneKeyword) != std::string::npos){
			isTaskMarkedAsDone = true;
			extractedSingleLine = extractedSingleLine.substr(0, extractedSingleLine.size() - 5);
		}
		data = data.substr(end + 1, data.size() - end);
		loadTaskPtr = new Task;
		(*loadTaskPtr).addDetails(extractedSingleLine);
		if (isTaskMarkedAsDone){
			(*loadTaskPtr).markIsDoneAsTrue();
			isTaskMarkedAsDone = false;
		}

		addTask(*loadTaskPtr);
		
		delete loadTaskPtr;
		loadTaskPtr = NULL;
	}
}

/************************************************************************************************

Delete Helper Functions

************************************************************************************************/
//Private Functions

//@author A0111361Y
//generates and ID to attach to task
int Planner::getNewId(void){

	static int generatedID;
	if (All.empty()){
		generatedID = 10001;
	}
	else generatedID++;
	return generatedID;
}

//@author A0111361Y
string Planner::deleteIndex(int idNumber){
	list<Task> ::iterator taskIter, deleteTargetIter;
	string status;

	taskIter = All.begin();
	for (taskIter = All.begin(); taskIter != All.end(); ++taskIter){
		if ((*taskIter).getIdNumber() == idNumber){
			deleteTargetIter = taskIter;
		}
	}

	updateLastEntryStructure(COMMAND_DELETE, *deleteTargetIter);

	All.erase(deleteTargetIter);
	status = statusToString(COMMAND_DELETE, *deleteTargetIter);
	
	checkListForClashes();
	generateAllOtherList();

	//logging
	stringstream message;
	message << LOG_FILE_DELETE_TASK_INTRO_MSG << idNumber;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());

	return status;
}

/************************************************************************************************

"Undo" Helper Functions

************************************************************************************************/
//Private Functions

//@author A0111361Y
//Updates the lastEntry Structure
void Planner::updateLastEntryStructure(string command, Task theTask){

	lastEntry.lastCommand = command;
	lastEntry.lastTask = theTask;
}

/************************************************************************************************

"Mark Done" Helper Functions

************************************************************************************************/
//Private Functions

//@author A0111361Y
string Planner::markDoneIndex(int idNumber){
	list<Task> ::iterator taskIter;
	string status;
	
	for (taskIter = All.begin(); taskIter != All.end(); ++taskIter){
		if ((*taskIter).getIdNumber() == idNumber){
			(*taskIter).markIsDoneAsTrue();
			status = statusToString(COMMAND_DONE, (*taskIter));
			break;
		}
	}

	checkListForClashes();
	generateAllOtherList();

	//logging
	stringstream message;
	message << LOG_FILE_MARK_DONE_MSG << idNumber;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());

	return status;
}

/************************************************************************************************

Duplicate Helper Functions

************************************************************************************************/
//Private Functions

//@author A0111361Y
bool Planner::isDuplicatePresent(Task newTask){
	list<Task> ::iterator taskIter;
	for (taskIter = All.begin(); taskIter != All.end(); ++taskIter){
		if (tasksAreTheSame(newTask, (*taskIter))){
			return true;
		}
	}
	return false;
}

//@author A0111361Y
bool Planner::tasksAreTheSame(Task Task1, Task Task2){
	bool same = true;
	string descriptionOfTask1 = Task1.getDescription();
	string descriptionOfTask2 = Task2.getDescription();
	
	if (descriptionOfTask1 != descriptionOfTask2){
		same = false;
	}
	if (!(Task1.areDatesTheSame(Task1.getDateStart(), Task2.getDateStart()))){
		same = false;
	}
	if (!(Task1.areDatesTheSame(Task1.getDateEnd(), Task2.getDateEnd()))){
		same = false;
	}
	if (Task1.getImportance() != Task2.getImportance()){
		same = false;
	}
	if (Task1.getTimeEnd() != Task2.getTimeEnd()){
		same = false;
	}
	if (Task1.getTimeStart() != Task2.getTimeStart()){
		same = false;
	}

	return same;
}

/************************************************************************************************

Clash Helper Functions

************************************************************************************************/
//Private Functions

//@author A0111361Y
void Planner::clearClashList(){
	list<Task> ::iterator taskIter;

	taskIter = All.begin();
	while (taskIter != All.end()){
		(*taskIter).markClashAsFalse();
		taskIter++;
	}
}

//@author A0111361Y
void Planner::checkListForClashes(){
	list<Task> ::iterator taskIter1, taskIter2;
	
	clearClashList();

	for (taskIter1 = All.begin(); taskIter1 != All.end(); ++taskIter1){
		for (taskIter2 = taskIter1; taskIter2 != All.end(); ++taskIter2){
			if (taskIter1 != taskIter2){
				if (checkTaskForClashes((*taskIter1), (*taskIter2))){
					(*taskIter1).markClashAsTrue();
					(*taskIter2).markClashAsTrue();
				}
			}
		}
	}

}

//@author A0111061E
bool Planner::checkTaskForClashes(Task Task1, Task Task2){
	bool isClash = false;
	int numOfTask1Times, numOfTask2Times, numOfTask1Dates, numOfTask2Dates, task1StartTime, task2StartTime;

	numOfTask1Times = Task1.getNumOfTimes();
	numOfTask2Times = Task2.getNumOfTimes();
	numOfTask1Dates = Task1.getNumOfDates();
	numOfTask2Dates = Task2.getNumOfDates();

	task1StartTime = Task1.getTimeStart();
	task2StartTime = Task2.getTimeStart();


	//Floating tasks and tasks with no times specified
	if ((numOfTask1Dates == 0 && numOfTask2Dates == 0 && numOfTask1Times == 0 && numOfTask2Times == 0) || (numOfTask1Times == 0 || numOfTask2Times == 0)){
		isClash = false;
	}

	//Both tasks have 2 dates and 1 time
	else if (numOfTask1Dates == 2 && numOfTask2Dates == 2 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (isTwoDatesTasksSameDates(Task1, Task2)){
			if (task1StartTime == task2StartTime){
				isClash = true;
			}
		}
	}

	//Both tasks have 2 dates 2 times
	else if (numOfTask1Dates == 2 && numOfTask2Dates == 2 && numOfTask1Times == 2 && numOfTask2Times == 2){
		if (isTwoDatesTasksSameDates(Task1, Task2)){
			if (taskTimesOverlap(Task1, Task2)){
				isClash = true;
			}
		}
	}

	//Both tasks have 1 date 1 time
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 1 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (isOneDateTasksSameDates(Task1, Task2)){
			if (task1StartTime == task2StartTime){
				isClash = true;
			}
		}
	}

	//Both tasks have 1 date 2 times
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 1 && numOfTask1Times == 2 && numOfTask2Times == 2){
		if (isOneDateTasksSameDates(Task1, Task2)){
			if (taskTimesOverlap(Task1, Task2)){
				isClash = true;
			}
		}
	}

	//Both tasks have no date 1 time
	else if (numOfTask1Dates == 0 && numOfTask2Dates == 0 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (task1StartTime == task2StartTime){
			isClash = true;
		}
	}

	//Both tasks have no date 2 times
	else if (numOfTask1Dates == 0 && numOfTask2Dates == 0 && numOfTask1Times == 2 && numOfTask2Times == 2){
		if (taskTimesOverlap(Task1, Task2)){
			isClash = true;
		}
	}

	//Task1 has 1 date 1 time and Task2 has 2 dates, 1 time
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 2 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (isOneDateTaskbetweenTwoDateTask(Task1, Task2)){
			if (task1StartTime == task2StartTime){
				isClash = true;
			}
		}
	}

	//opposite of above: Task1 has 2 dates 1 time, task2 has 1 date and 1 time
	else if (numOfTask1Dates == 2 && numOfTask2Dates == 1 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (isOneDateTaskbetweenTwoDateTask(Task2, Task1)){
			if (task1StartTime == task2StartTime){
				isClash = true;
			}
		}
	}

	//Task1 has 1 date 1 time and Task2 has 2 dates, 2 time
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 2 && numOfTask1Times == 1 && numOfTask2Times == 2){
		isClash = isClashTaskSingleDateTimeTaskDoubleDateTime(Task1, Task2);
	}

	//opp of above: Task1 has 2 dates 2 times, task2 has 1 date 1 time
	else if (numOfTask1Dates == 2 && numOfTask2Dates == 1 && numOfTask1Times == 2 && numOfTask2Times == 1){
		isClash = isClashTaskSingleDateTimeTaskDoubleDateTime(Task2, Task1);
	}

	return isClash;
}

//@author A0111061E
bool Planner::isClashTaskSingleDateTimeTaskDoubleDateTime(Task Task1, Task Task2){
	bool isClash = false;

	if (isOneDateTaskbetweenTwoDateTask(Task1, Task2)){
		if (isOneTimeTaskBetweenTwoTimesTask(Task1, Task2)){
			isClash = true;
		}
	}

	return isClash;
}

//@author A0111061E
bool Planner::isTwoDatesTasksSameDates(Task Task1, Task Task2){
	bool areEqual = false;

	if (Task1.getDateStart().year == Task2.getDateStart().year && Task1.getDateEnd().year == Task2.getDateEnd().year) {
		if (Task1.getDateStart().month == Task2.getDateStart().month && Task1.getDateEnd().month == Task2.getDateEnd().month) {
			if (Task1.getDateStart().day == Task2.getDateStart().day && Task1.getDateEnd().day == Task2.getDateEnd().day){
				areEqual = true;
			}
		}
	}
	return areEqual;
}

//@author A0111061E
bool Planner::isOneDateTasksSameDates(Task Task1, Task Task2){
	bool dateIsEqual = false;

	if (Task1.getDateEnd().year == Task2.getDateEnd().year) {
		if (Task1.getDateEnd().month == Task2.getDateEnd().month) {
			if (Task1.getDateEnd().day == Task2.getDateEnd().day) {
				dateIsEqual = true;
			}
		}
	}

	return dateIsEqual;
}

//@author A0111061E
bool Planner::isOneTimeTaskBetweenTwoTimesTask(Task Task1, Task Task2){
	int task1StartTime, task2StartTime, task2EndTime;
	bool isInBetween = false;

	task1StartTime = Task1.getTimeStart();
	task2StartTime = Task2.getTimeStart();
	task2EndTime = Task2.getTimeEnd();

	if (task1StartTime < task2EndTime && task1StartTime >= task2StartTime){
		isInBetween = true;
	}
	return isInBetween;
}

//@author A0111061E
bool Planner::taskTimesOverlap(Task Task1, Task Task2){
	int task1StartTime, task2StartTime, task1EndTime, task2EndTime;
	bool isOverlap = false;

	task1StartTime = Task1.getTimeStart();
	task2StartTime = Task2.getTimeStart();
	task1EndTime = Task1.getTimeEnd();
	task2EndTime = Task2.getTimeEnd();

	if ((task1EndTime > task2StartTime && task1StartTime <= task2StartTime) || (task1StartTime < task2EndTime && task1EndTime >= task2EndTime)){
		isOverlap = true;
	}
	return isOverlap;
}

//@author A0111061E
bool Planner::isOneDateTaskbetweenTwoDateTask(Task Task1, Task Task2){
	bool isInBetween = false;
	taskDate task1StartDate, task1EndDate, task2StartDate, task2EndDate;
	int task1StartTime, task1EndTime, task2StartTime, task2EndTime;

	task1StartDate = Task1.getDateStart();
	task1EndDate = Task1.getDateEnd();
	task1StartTime = Task1.getTimeStart();
	task1EndTime = Task1.getTimeEnd();

	task2StartDate = Task2.getDateStart();
	task2EndDate = Task2.getDateEnd();
	task2StartTime = Task2.getTimeStart();
	task2EndTime = Task2.getTimeEnd();

	if (task1EndDate.year <= task2EndDate.year && task1EndDate.year >= task2StartDate.year) {
		if (task1EndDate.month <= task2EndDate.month && task1EndDate.month >= task2StartDate.month) {
			if (task1EndDate.day <= task2EndDate.day && task1EndDate.day >= task2StartDate.day) {
				isInBetween = true;
			}
		}
	}

	return isInBetween;
}

//@author A0111314A
//Function checks if an index is valid (exists and has been assigned to a task) and returns true if it is
bool Planner::indexChecker(list<Task>::iterator& taskIter, int serialNumber, list<Task>& targetList){
	int indexCount = STARTING_SERIAL_NUMBER;
	bool isValidIndex = true;

	taskIter = targetList.begin();
	for (size_t i = 1; i != serialNumber && i < targetList.size(); i++){
		taskIter++;
		indexCount++;
	}

	if (indexCount != serialNumber || targetList.empty()) {
		isValidIndex = false;
	}

	return isValidIndex;
}

/************************************************************************************************

Status Returning functions

************************************************************************************************/
//Private Functions

//@author A0111361Y FOLLOW KARTHIKS const STRING STANDARDS
string Planner::descriptionOfTaskToString(Task theTask){
	ostringstream out;
	int x = theTask.getTimeStart();
	out << theTask.getDescription() << " ";

	switch (theTask.getNumOfDates()){
	case 0:
		break;
	case 1:
		out << "Date: " << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
		break;
	case 2:
		out << "Date: " << theTask.getDateStart().day << "/" << theTask.getDateStart().month << "/" << theTask.getDateStart().year << " to ";
		out << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
		break;
	}

	switch (theTask.getNumOfTimes()){
	case 0:
		break;
	case 1:
		out << "Time: " << setfill('0') << setw(4) << theTask.getTimeStart() << " ";
		break;
	case 2:
		out << "Time: " << setfill('0') << setw(4) << theTask.getTimeStart();
		out << " to ";
		out << setfill('0') << setw(4) << theTask.getTimeEnd() << " ";
		break;
	default:
		throw ERROR_MESSAGE_FATAL;
	}



	if (theTask.getImportance()){
		out << IMPORTANCE_SYMBOL;
	}

	if (theTask.clashStatus() == true){
		out << CLASH_KEYWORD;
	}
	return out.str();
}

//@author A0111361Y
string Planner::addStatusToString(Task theTask){
	ostringstream out;

	out << STATUS_TO_STRING_ADD_INTRO;
	out << descriptionOfTaskToString(theTask);
	out << NEWLINE;

	return out.str();
}

//@author A0111361Y
string Planner::deleteStatusToString(Task theTask){
	ostringstream out;

	out << STATUS_TO_STRING_DELETE_INTRO;
	out << descriptionOfTaskToString(theTask);
	out << NEWLINE;

	return out.str();
}

//@author A0111361Y
string Planner::editStatusToString(){
	ostringstream out;

	out << STATUS_TO_STRING_EDIT_INTRO;
	out << descriptionOfTaskToString(lastEdit.deletedTask);
	out << STATUS_TO_STRING_EDIT_MID;
	out << descriptionOfTaskToString(lastEdit.addedTask);

	return out.str();
}

//@author A0111361Y
string Planner::undoStatusToString(){
	ostringstream out;

	if (lastEntry.lastCommand == COMMAND_ADD){
		out << STATUS_TO_STRING_UNDO_ADD_MSG;
		out << descriptionOfTaskToString(lastEntry.lastTask);
	}
	else if (lastEntry.lastCommand == COMMAND_DELETE){
		out << STATUS_TO_STRING_UNDO_DELETE_MSG;
		out << descriptionOfTaskToString(lastEntry.lastTask);
	}
	else if (lastEntry.lastCommand == COMMAND_EDIT){
		out << STATUS_TO_STRING_EDIT_INTRO;
		out << descriptionOfTaskToString(lastEdit.addedTask);
		out << STATUS_TO_STRING_EDIT_MID;
		out << descriptionOfTaskToString(lastEdit.deletedTask);
	}
	else{
		throw ERROR_MESSAGE_INVALID_UNDO;
	}
	return out.str();
}

//@author A0111361Y
string Planner::clearStatusToString(){
	return STATUS_TO_STRING_CLEAR_MSG;
}

//@author A0111361Y
string Planner::saveStatusToString(){
	return STATUS_TO_STRING_SAVE_MSG;
}

//@author A0111361Y
string Planner::searchStatusToString(){
	return SEARCH_RESULTS_MSG;
}

//@author A0111361Y
string Planner::doneStatusToString(){
	return STATUS_TO_STRING_DONE_MSG;
}

//@author A0111361Y
string Planner::duplicateStatusToString(Task theTask){
	ostringstream out;
	out << STATUS_TO_STRING_DUPLICATE_MSG;
	out << descriptionOfTaskToString(theTask);
	out << NEWLINE;
	return out.str();

}

/************************************************************************************************

Lists Generating Functions

************************************************************************************************/
//Private Functions 
//REFACTORED @ Sakib
//@author A0111361Y
void Planner::generateAllOtherList(void){
	clearTheLists();
	generateTheLists();
}

//@author A0111314A
//Function generates an iterator that goes through all tasks and checks if it belongs in HomeList. 
//if yes, it pushes it into the list. 
void Planner::generateHomeList(void){
	list<Task> ::iterator it;

	for (it = All.begin(); it != All.end(); ++it){
		if (isHome(currentDate, it)) {
			homeList.push_back(*it);
		}
	}
}

//@author A0111314A
//Function generates an iterator that goes through all tasks and checks if it belongs in UpcomingList. 
//if yes, it pushes it into the list. 
void Planner::generateUpcomingList(void){
	list<Task> ::iterator iter;

	for (iter = All.begin(); iter != All.end(); ++iter){
		if (isUpcoming(currentDate, iter)) {
			upcomingList.push_back(*iter);
		}
	}
}

//@author A0111314A
//Function generates an iterator that goes through all tasks and checks if it belongs in MissedList. 
//if yes, it pushes it into the list. 
void Planner::generateMissedList(void){
	list<Task> ::iterator iter;

	for (iter = All.begin(); iter != All.end(); ++iter){
		if (isMissed(currentDate, iter)) {
			missedList.push_back(*iter);
		}
	}
}

//@author A0111361Y
void Planner::generateDoneList(void){
	list<Task> ::iterator it;

	for (it = All.begin(); it != All.end(); ++it){
		if ((*it).doneStatus() == true) {
			doneList.push_back(*it);
		}
	}
}

//@author A0111361Y
void Planner::clearTheLists(void){
	homeList.clear();
	missedList.clear();
	upcomingList.clear();
	doneList.clear();
}

//@author A0111361Y
void Planner::generateTheLists(void){
	generateHomeList();
	generateMissedList();
	generateUpcomingList();
	generateDoneList();
}

/************************************************************************************************

Generator Logic Functions

************************************************************************************************/
//Private Functions
//assumes 30 days in a month

//@author A0111314A
//Function checks if task should be included in Home view and returns true if it is.
bool Planner::isHome(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinHome = false;

	int startDay, startMonth, startYear;
	int endDay, endMonth, endYear;

	startDay = (*it).getDateStart().day;
	startMonth = (*it).getDateStart().month;
	startYear = (*it).getDateEnd().year;
	endDay = (*it).getDateEnd().day;
	endMonth = (*it).getDateEnd().month;
	endYear = (*it).getDateEnd().year;

	//case 1: accept if start date is within the next 7 days
	if (checkHomeDate(currentDate, startDay, startMonth, startYear)){
		isWithinHome = true;
	}

	//case 2: accept if end date is within the next 7 days
	if (checkHomeDate(currentDate, endDay, endMonth, endYear)){
		isWithinHome = true;
	}

	//case 3: floating task
	if ((*it).getNumOfDates() == 0) {
		isWithinHome = true;
	}

	//case 4: reject if task is done
	if ((*it).doneStatus()){
		isWithinHome = false;
	}

	return isWithinHome;
}

//@author A0111314A
//Function checks that task date is within 7 days of current date
bool Planner::checkHomeDate(taskDate currentDate, int day, int month, int year){
	bool isWithinHome = false;

	//case 1: currentDate + 7 days = current month, same year (date end)
	if (currentDate.day <= 23) {
		if (month == (currentDate.month)) {
			if (day <= (currentDate.day + 7) && day >= currentDate.day) {
				if (year == currentDate.year) {
					isWithinHome = true;
				}
			}
		}
	}
	//case 2: currentDate + 7 days = next month, task = current month, not december (date end)
	else if (month == (currentDate.month)) {
		if (year == currentDate.year) {
			if (day <= 31 && day >= currentDate.day) {
				isWithinHome = true;
			}
		}
	}
	//case 3:  currentDate + 7 days = next month, task = next month, not december (date end)
	else if (month == (currentDate.month + 1)) {
		if (year == currentDate.year) {
			if (day < (7 - (30 - currentDate.day))) {
				isWithinHome = true;
			}
		}
	}
	//case 4: current date + 7 days = next month, december (date end)
	else if (year == (currentDate.year + 1)) {
		if (month == 1) {
			if (day < (7 - (30 - currentDate.day))) {
				isWithinHome = true;
			}
		}
	}

	return isWithinHome;
}

//@author A0111314A
//Function checks if tsk should be in Missed view and returns true if it is
bool Planner::isMissed(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinMissed = false;

	int endDay, endMonth, endYear;

	endDay = (*it).getDateEnd().day;
	endMonth = (*it).getDateEnd().month;
	endYear = (*it).getDateEnd().year;

	//case 1: reject if date has not passed
	if (checkMissedDate(currentDate, endDay, endMonth, endYear)){
		isWithinMissed = true;
	}

	//case 2: reject floating tasks
	if ((*it).getNumOfDates() == 0) {
		isWithinMissed = false;
	}

	//case 3: reject tasks that are already done
	if ((*it).doneStatus()){
		isWithinMissed = false;
	}

	return isWithinMissed;
}

//@author A0111314A
//Function checks if task date has passed
bool Planner::checkMissedDate(taskDate currentDate, int endDay, int endMonth, int endYear){
	bool isWithinMissed = false;

	//case 1: passed year
	if (endYear < currentDate.year) {
		isWithinMissed = true;
	}
	//case 2: same year, passed month
	else if (endYear == currentDate.year) {
		if (endMonth < currentDate.month) {
			isWithinMissed = true;
		}//case 3: same year, same month, passed day
		else if (endMonth == currentDate.month) {
			if (endDay < currentDate.day) {
				isWithinMissed = true;
			}
		}
	}

	return isWithinMissed;
}

//@author A0111314A
//Function checks if task should be in Upcoming view and returns true if it is.
bool Planner::isUpcoming(taskDate currentDate, list<Task>::iterator it){
	bool isWithinUpcoming = true;

	//case 1: reject if task is in home
	if (isHome(currentDate, it)){
		isWithinUpcoming = false;
	}

	//case 2: reject if task is in missed
	if (isMissed(currentDate, it)){
		isWithinUpcoming = false;
	}

	//case 3: reject floating tasks
	if ((*it).getNumOfDates() == 0) {
		isWithinUpcoming = false;
	}

	//case 4: reject tasks that are already done
	if ((*it).doneStatus()){
		isWithinUpcoming = false;
	}

	return isWithinUpcoming;
}

/************************************************************************************************

List Returning Functions

************************************************************************************************/
//Private Functions
// REFACTORED @ Sakib
//@author A0111361Y
string Planner::homeListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = homeList.begin();
	int serialNumber = 1;
	if (!homeList.empty()){
		for (it = homeList.begin(); it != homeList.end(); ++it){
			out << serialNumber << ". ";
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << EMPTY_LIST_MESSAGE << endl;

	return out.str();
}

//@author A0111361Y
string Planner::upcomingListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = upcomingList.begin();
	int serialNumber = 1;
	if (!upcomingList.empty()){
		for (it = upcomingList.begin(); it != upcomingList.end(); ++it){
			out << serialNumber << ". ";
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << EMPTY_LIST_MESSAGE << endl;

	return out.str();
}

//@author A0111361Y
string Planner::missedListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = missedList.begin();
	int serialNumber = 1;
	if (!missedList.empty()){
		for (it = missedList.begin(); it != missedList.end(); ++it){
			out << serialNumber << ". ";
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << EMPTY_LIST_MESSAGE << endl;

	return out.str();
}

//@author A0111361Y
string Planner::searchListToString(void){

	ostringstream out;
	list<Task> ::iterator it;
	it = searchList.begin();
	int serialNumber = 1;
	if (!searchList.empty()){
		for (it = searchList.begin(); it != searchList.end(); ++it){
			out << serialNumber << ". ";
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << NO_RESULTS_MESSAGE << endl;

	return out.str();
}

//@author A0111361Y
string Planner::doneListToString(){
	ostringstream out;
	list<Task> ::iterator it;
	it = doneList.begin();
	int serialNumber = 1;
	if (!doneList.empty()){
		for (it = doneList.begin(); it != doneList.end(); ++it){
			out << serialNumber << ". ";
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << EMPTY_LIST_MESSAGE << endl;
	return out.str();
}

//@author A0111314A
//Function checks if missed list is empty. If it is not, return false.
bool Planner::isMissedEmpty(){
	bool missedEmpty = true;

	if (!missedList.empty()){
		missedEmpty = false;
	}

	return missedEmpty;
}

