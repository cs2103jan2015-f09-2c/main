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

const string DUPLICATE_STATUS = "duplicate";

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

const string EMPTY_LIST_MESSAGE = "The list is empty";
const string NO_RESULTS_MESSAGE = "No results found!";
const string NEWLINE = "\r\n";
const string IMPORTANCE_SYMBOL = "#impt";

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



using namespace std;

/************************************************************************************************

										Initialization

************************************************************************************************/

Planner::Planner(){
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	currentDate.year = (now->tm_year - 100);
	currentDate.month = (now->tm_mon + 1);
	currentDate.day = (now->tm_mday);
}

/************************************************************************************************

									Planner4Life operations

************************************************************************************************/

string Planner::addTask(Task newTask){
	//create new task
	int id = getIdOfLastEntry(); // use static to actually create id

	//logging
	stringstream message;
	message << LOG_FILE_ADD_TASK_INTRO_MSG << id;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());
	newTask.storeIdNumber(id);

	//check for duplicate
	bool duplicatePresent = false;
	duplicatePresent=isDuplicatePresent(newTask);
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
	
	lastEntry.lastCommand = COMMAND_ADD;
	lastEntry.lastTask = newTask;
	checkListForClashes();
	generateAllOtherList();

	return status;
}

void Planner::checkListForClashes(){
	list<Task> ::iterator it;
	it = All.begin();
	while (it != All.end()){
		(*it).markClashAsFalse();
		it++;
	}
	list<Task> ::iterator iter1, iter2;
	for (iter1 = All.begin(); iter1 != All.end(); ++iter1){
			for (iter2 = iter1; iter2 != All.end(); ++iter2){
				if (iter1 != iter2){
					if (checkTaskForClashes((*iter1), (*iter2))){
						(*iter1).markClashAsTrue();
						(*iter2).markClashAsTrue();
					}
				}
			}
	}

	
	return;
	
}

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

bool Planner::isOneDateTaskbetweenTwoDateTask(Task taskWithOneDate, Task taskWithTwoDates){
	bool isInBetween = false;

	if (taskWithOneDate.getDateEnd().year <= taskWithTwoDates.getDateEnd().year && taskWithOneDate.getDateEnd().year >= taskWithTwoDates.getDateEnd().year) {
		if (taskWithOneDate.getDateEnd().month <= taskWithTwoDates.getDateEnd().month && taskWithOneDate.getDateEnd().month >= taskWithTwoDates.getDateEnd().month) {
			if (taskWithOneDate.getDateEnd().day <= taskWithTwoDates.getDateEnd().day && taskWithOneDate.getDateEnd().day >= taskWithTwoDates.getDateEnd().day){
				isInBetween = true;
			}
		}
	}
	return isInBetween;
}

bool Planner::checkTaskForClashes(Task Task1, Task Task2){
	bool isClash = false;
	int numOfTask1Times, numOfTask2Times, numOfTask1Dates, numOfTask2Dates, task1StartTime, task2StartTime;
	
	numOfTask1Times = Task1.getNumOfTimes();
	numOfTask2Times = Task2.getNumOfTimes();
	numOfTask1Dates = Task1.getNumOfDates();
	numOfTask2Dates = Task2.getNumOfDates();

	task1StartTime = Task1.getTimeStart();
	task2StartTime = Task2.getTimeStart();
	
	if (numOfTask1Times == 0 || numOfTask2Times == 0){
		return isClash;
	}

	//Both tasks have 2 dates and 1 time
	else if (numOfTask1Dates == 2 && numOfTask2Dates == 2 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (isTwoDatesTasksSameDates(Task1, Task2)){
			if (task1StartTime == task2StartTime){
				isClash = true;
			}
		}
	}
	

	//Both tasks have 2 dates 2 times*******check sign here and refactor out
	else if (numOfTask1Dates == 2 && numOfTask2Dates == 2 && numOfTask1Times == 2 && numOfTask2Times == 2){
		if (isTwoDatesTasksSameDates(Task1, Task2)){
			if ((Task1.getTimeEnd() >= task2StartTime && task1StartTime <= task2StartTime) || (task1StartTime <= Task2.getTimeEnd() && Task1.getTimeEnd() >= Task2.getTimeEnd())){
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
	
	//Both tasks have 1 date 2 time********check sign here and refactor out
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 1 && numOfTask1Times == 2 && numOfTask2Times == 2){
		if (isOneDateTasksSameDates(Task1, Task2)){
			if ((Task1.getTimeEnd() > task2StartTime && task1StartTime <= task2StartTime) || (task1StartTime <= Task2.getTimeEnd() && Task1.getTimeEnd() >= Task2.getTimeEnd())){
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

	//Task1 has 1 date 1 time and Task2 has 2 dates, 1 time
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 2 && numOfTask1Times == 1 && numOfTask2Times == 1){
		if (isOneDateTaskbetweenTwoDateTask(Task1, Task2)){
			if (task1StartTime == task2StartTime){
				isClash = true;
			}
		}
	}
	
	//Floating tasks
	else if (numOfTask1Dates == 0 && numOfTask2Dates == 0 && numOfTask1Times == 0 && numOfTask2Times == 0){
		isClash = false;
	}

	//Task1 has 1 date 1 time and Task2 has 2 dates, 2 time
	else if (numOfTask1Dates == 1 && numOfTask2Dates == 2 && numOfTask1Times == 1 && numOfTask2Times == 2){
		isClash = isClashTaskSingleDateTimeTaskDoubleDateTime(Task2, Task1);
	}
	else {
		isClash = isClashTaskSingleDateTimeTaskDoubleDateTime(Task1, Task2);
	}

	return isClash;
}

//should this be  end1 year <= end2 year && end1 >= start2
bool Planner::isClashTaskSingleDateTimeTaskDoubleDateTime(Task Task1, Task Task2){
	bool isClash = false;
	if (Task1.getDateEnd().year <= Task2.getDateEnd().year && Task1.getDateEnd().year >= Task2.getDateEnd().year) {
		if (Task1.getDateEnd().month <= Task2.getDateEnd().month && Task1.getDateEnd().month >= Task2.getDateEnd().month) {
			if (Task2.getDateEnd().day <= Task1.getDateEnd().day && Task2.getDateEnd().day >= Task1.getDateStart().day) {
				if ((Task1.getTimeEnd() >= Task2.getTimeStart() && Task1.getTimeStart() <= Task2.getTimeStart()) || (Task1.getTimeStart() <= Task2.getTimeEnd() && Task1.getTimeEnd() >= Task2.getTimeEnd())){
					isClash = true;
				}
			}
		}
	}

	return isClash;
}

bool Planner::isDuplicatePresent(Task newTask){
	list<Task> ::iterator iter;
	for (iter = All.begin(); iter != All.end(); ++iter){
		if (tasksAreTheSame(newTask, (*iter))){
			return true;
		}
	}
	return false;

}

bool Planner::tasksAreTheSame(Task Task1, Task Task2){
	bool same = true;
	string s = Task1.getDescription();
	string t = Task2.getDescription();
	t = t.substr(0, t.end() - t.begin());
	if (s != t){// i dont know why but this does not work if i just put in the Task.getdescriptions, so i put 2 strings
		
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

bool Planner::indexChecker(list<Task>::iterator& iter, int serialNumber, list<Task>& targetList){
	int indexCount = 1;
	bool isValidIndex = true;

	iter = targetList.begin();
	for (int i = 1; i != serialNumber && i < targetList.size(); i++){
		iter++;
		indexCount++;
	}
	if (indexCount != serialNumber || targetList.empty()) {
		isValidIndex = false;
	}

	return isValidIndex;
}

string Planner::deleteTask(int serialNumber, string nameOfList){
	int idNumber;
	string status;
	list<Task> ::iterator iter;

	if (nameOfList == HOME_LIST){
		if (indexChecker(iter, serialNumber, HomeList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*iter).getIdNumber();
			status = deleteIndex(idNumber);
		}
	}
	else if (nameOfList == MISSED_LIST){
		if (indexChecker(iter, serialNumber, MissedList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*iter).getIdNumber();
			status = deleteIndex(idNumber);
		}
	}
	else if (nameOfList == UPCOMING_LIST){
		if (indexChecker(iter, serialNumber, UpcomingList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*iter).getIdNumber();
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

string Planner::deleteIndex(int idNumber){
	list<Task> ::iterator iter1, iter2;
	iter1 = All.begin();
	for (iter1 = All.begin(); iter1 != All.end(); ++iter1){
		if ((*iter1).getIdNumber() == idNumber){
			iter2 = iter1;
		}
	}
	lastEntry.lastTask = *iter2;
	lastEntry.lastCommand = COMMAND_DELETE;
	string status;
	status = statusToString(COMMAND_DELETE, *iter2);
	All.erase(iter2);
	
	generateAllOtherList();
	//logging
	stringstream message;
	message << LOG_FILE_DELETE_TASK_INTRO_MSG << idNumber;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());

	return status;
}

string Planner::undo(void){
	string status = "";
	if (lastEntry.lastCommand == COMMAND_ADD){
		int lastEntryID = getIdOfLastEntry() - 1;
		deleteIndex(lastEntryID);
	}
	else if (lastEntry.lastCommand == COMMAND_DELETE){
		addTask(lastEntry.lastTask);
	}
	else if (lastEntry.lastCommand == COMMAND_EDIT){
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

string Planner::clear(void){
	All.clear();
	generateAllOtherList();
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, LOG_FILE_CLEAR_TASK_MSG);
	return clearStatusToString();
}

string Planner::editTask(int serialNumber, string nameOfList, string input){
	Task newTask;
	string validEditCheck;
	newTask.addDetails(input);
	validEditCheck = deleteTask(serialNumber, nameOfList);
	
	if (validEditCheck == ERROR_MESSAGE_INVALID_INDEX) {
		return validEditCheck;
	}
	else {
		lastEdit.deletedTask = lastEntry.lastTask;
		addTask(newTask);
		lastEdit.addedTask = lastEntry.lastTask;
		lastEntry.lastCommand = COMMAND_EDIT;
		
		generateAllOtherList();
		LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, LOG_FILE_EDIT_TASK_MSG);
		return editStatusToString();
	}
}


void Planner::loadData(string data){
	Task* tempTask;
	string tempString, dataCopy = data;
	size_t start = 0, end = 0;
	All.clear();

	while (dataCopy.size()>0){
		end = dataCopy.find_first_of("\n");
		tempString = dataCopy.substr(start, end - start);
		dataCopy = dataCopy.substr(end+1, dataCopy.size() - end);
		tempTask = new Task;
		(*tempTask).addDetails(tempString);
		addTask(*tempTask);
		delete tempTask;
		tempTask = NULL;
	}
}

int Planner::getIdOfLastEntry(void){// act this function returns id not last entry, need to change name

	static int idGeneratror;
	if (All.empty()){
		idGeneratror = 10001;
	}
	else idGeneratror++;
	return idGeneratror;
}

string Planner::markDone(int serialNumber, string nameOfList){
	int idNumber=0;
	string status;
	list<Task> ::iterator iter;

	if (nameOfList == HOME_LIST){
		if (indexChecker(iter, serialNumber, HomeList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*iter).getIdNumber();
			status = markDoneIndex(idNumber);
		}
	}
	else if (nameOfList == MISSED_LIST){
		if (indexChecker(iter, serialNumber, MissedList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*iter).getIdNumber();
			status = markDoneIndex(idNumber);
		}
	}
	else if (nameOfList == UPCOMING_LIST){
		if (indexChecker(iter, serialNumber, UpcomingList) == false){
			throw ERROR_MESSAGE_INVALID_INDEX;
		}
		else {
			idNumber = (*iter).getIdNumber();
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

string Planner::markDoneIndex(int idNumber){
	list<Task> ::iterator iter1;
	iter1 = All.begin();
	string status;
	for (iter1 = All.begin(); iter1 != All.end(); ++iter1){
		if ((*iter1).getIdNumber() == idNumber){
			(*iter1).markIsDoneAsTrue();
			status = statusToString(COMMAND_DONE, (*iter1));
			break;
		}
	}

	generateAllOtherList();
	//logging
	stringstream message;
	message << LOG_FILE_MARK_DONE_MSG << idNumber;
	LogData->addLog(LOG_FILE_UPDATE_KEY_WORD, message.str());

	return status;

}

/************************************************************************************************

										Printing functions

************************************************************************************************/

string Planner::toString(string nameOfList){
	//convert the list to a string and return
	string finalString;
	if (nameOfList == HOME_LIST){
		finalString = HomeListToString();
		return finalString;
	}
	else if (nameOfList == UPCOMING_LIST){
		finalString = upcomingListToString();
		return finalString;
	}
	else if (nameOfList == MISSED_LIST){
		finalString = missedListToString();
		return finalString;
	}
	else if (nameOfList == SEARCH_LIST){
		finalString = searchListToString();
		return finalString;
	}
	else if (nameOfList == DONE_LIST){
		finalString = doneListToString();
		return finalString;
	}
	else return ERROR_MESSSAGE_INVALID_LIST_NAME;
}

string Planner::AllToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = All.begin();
	int serialNumber = 1;
	int entryCount = 0;
	if (!All.empty()){
		for (it = All.begin(); it != All.end(); ++it){
			out << serialNumber << ". ";
			out<<descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
			entryCount++;
		}
	}
	else {
		out << EMPTY_LIST_MESSAGE << endl;
	}
	return out.str();
}

string Planner::statusToString(string command, Task theTask){
	string finalString;
	if (command == COMMAND_ADD){
		finalString = addStatusToString(theTask);
		return finalString;
	}
	else if (command == COMMAND_DELETE){
		finalString = deleteStatusToString(theTask);
		return finalString;
	}
	else if (command == COMMAND_EDIT){
		finalString = editStatusToString();
		return finalString;
	}
	else if (command == COMMAND_UNDO){
		finalString = undoStatusToString();
		return finalString;
	}
	else if (command == COMMAND_CLEAR){
		finalString = clearStatusToString();
		return finalString;
	}
	else if (command == COMMAND_SAVE){
		finalString = saveStatusToString();
		return finalString;
	}
	else if (command == COMMAND_DONE){
		finalString = doneStatusToString();
		return finalString;
	}
	else if (command == DUPLICATE_STATUS){
		finalString = duplicateStatusToString(theTask);
		return finalString;
	}
	else return ERROR_MESSSAGE_INVALID_COMMAND;
}

//Private Functions
string Planner::descriptionOfTaskToString(Task theTask){
	ostringstream out;
	int length;
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
		out << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " " ;
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

	if (theTask.doneStatus()==true){
		out << " DONE";
	}

	if (theTask.clashStatus() == true){
		out << "TASK CLASH!!!";
	}
	return out.str();
}

string Planner::addStatusToString(Task theTask){
	ostringstream out;
	out << STATUS_TO_STRING_ADD_INTRO;
	out << descriptionOfTaskToString(theTask);
	out << NEWLINE;
	return out.str();
}

string Planner::deleteStatusToString(Task theTask){
	ostringstream out;
	out << STATUS_TO_STRING_DELETE_INTRO;
	out << descriptionOfTaskToString(theTask);
	out << NEWLINE;
	return out.str();
}

string Planner::editStatusToString(){ // to be completed after undo edit works
	ostringstream out;
	out <<STATUS_TO_STRING_EDIT_INTRO;
	out << descriptionOfTaskToString(lastEdit.deletedTask);
	out << STATUS_TO_STRING_EDIT_MID;
	out << descriptionOfTaskToString(lastEdit.addedTask);
	return out.str();
}

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

string Planner::clearStatusToString(){
	return STATUS_TO_STRING_CLEAR_MSG;
}

string Planner::duplicateStatusToString(Task theTask){
	ostringstream out;
	out << STATUS_TO_STRING_DUPLICATE_MSG;
	out << descriptionOfTaskToString(theTask);
	out << NEWLINE;
	return out.str();
	
}

string Planner::saveStatusToString(){
	return STATUS_TO_STRING_SAVE_MSG;
}

string Planner::doneStatusToString(){
	return STATUS_TO_STRING_DONE_MSG;
}

string Planner::searchStatusToString(){
	return SEARCH_RESULTS_MSG;
}

string Planner::HomeListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = HomeList.begin();
	int serialNumber = 1;
	if (!HomeList.empty()){
		for (it = HomeList.begin(); it != HomeList.end(); ++it){
			out << serialNumber << ". ";
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << EMPTY_LIST_MESSAGE << endl;

	return out.str();
}

string Planner::upcomingListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = UpcomingList.begin();
	int serialNumber = 1;
	if (!UpcomingList.empty()){
		for (it = UpcomingList.begin(); it != UpcomingList.end(); ++it){
			out << serialNumber << ". " ;
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out <<EMPTY_LIST_MESSAGE << endl;

	return out.str();
}

string Planner::missedListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = MissedList.begin();
	int serialNumber = 1;
	if (!MissedList.empty()){
		for (it = MissedList.begin(); it != MissedList.end(); ++it){
			out << serialNumber << ". " ;
			out << descriptionOfTaskToString(*(it));
			out << NEWLINE;
			serialNumber = serialNumber + 1;
		}
	}
	else out << EMPTY_LIST_MESSAGE << endl;

	return out.str();
}

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

								Generation of Planner4Life Lists

************************************************************************************************/

void Planner::generateAllOtherList(void){
	HomeList.clear();
	MissedList.clear();
	UpcomingList.clear();
	doneList.clear();
	generateHomeList();
	generateMissedList();
	generateUpcomingList();
	generateDoneList();
}

string Planner::generateSearchList(string target){
	list<Task> ::iterator iter;
	Task tempTask;
	string status;
	searchList.clear();
	for (iter = All.begin(); iter != All.end(); ++iter){
		tempTask = *iter;
		if (tempTask.isSearchTargetPresent(target)){
			searchList.push_back(tempTask);
		}
	}

	return searchStatusToString();
}
void Planner::generateDoneList(void){
	list<Task> ::iterator it;

	for (it = All.begin(); it != All.end(); ++it){
		if ((*it).doneStatus()==true) {
			doneList.push_back(*it);
		}
	}
}
void Planner::generateHomeList(void){
	list<Task> ::iterator it;

	for (it = All.begin(); it != All.end(); ++it){
		if (isHome(currentDate, it)) {
			HomeList.push_back(*it);
		}
	}
}

void Planner::generateUpcomingList(void){
	list<Task> ::iterator iter;

	for (iter = All.begin(); iter != All.end(); ++iter){
		if (isUpcoming(currentDate, iter)) {
			UpcomingList.push_back(*iter);
		}
	}
}

void Planner::generateMissedList(void){
	list<Task> ::iterator iter;

	for (iter = All.begin(); iter != All.end(); ++iter){
		if (isMissed(currentDate, iter)) {
			MissedList.push_back(*iter);
		}
	}
}

/************************************************************************************************

										Generator Logic

************************************************************************************************/

//assumes 30 days in a month
bool Planner::isHome(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinHome = false;
	//case 1: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateStart().month == (currentDate.month)) {
			if ((*it).getDateStart().day <= (currentDate.day + 7) && (*it).getDateStart().day >= currentDate.day) {
				if ((*it).getDateStart().year == currentDate.year) {
					isWithinHome = true;
				}
			}
		}
	}
	//case 2: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateEnd().month == (currentDate.month)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day <= 31 && (*it).getDateEnd().day >= currentDate.day) {
				isWithinHome = true;
			}
		}
	}
	//case 3:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateEnd().month == (currentDate.month + 1)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day < (7 - (30 - currentDate.day))) {
				isWithinHome = true;
			}
		}
	}
	//case 4: current date + 7 days = next month, december
	else if ((*it).getDateEnd().year == (currentDate.year + 1)) {
		if ((*it).getDateEnd().month == 1) {
			if ((*it).getDateEnd().day < (7 - (30 - currentDate.day))) {
				isWithinHome = true;
			}
		}
	}
	//case 1a: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateStart().month == (currentDate.month)) {
			if ((*it).getDateStart().day <= (currentDate.day + 7) && (*it).getDateStart().day >= currentDate.day) {
				if ((*it).getDateStart().year == currentDate.year) {
					isWithinHome = true;
				}
			}
		}
	}
	//case 2a: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateStart().month == (currentDate.month)) {
		if ((*it).getDateStart().year == currentDate.year) {
			if ((*it).getDateStart().day <= 31 && (*it).getDateStart().day >= currentDate.day) {
				isWithinHome = true;
			}
		}
	}
	//case 3a:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateStart().month == (currentDate.month + 1)) {
		if ((*it).getDateStart().year == currentDate.year) {
			if ((*it).getDateStart().day < (7 - (30 - currentDate.day))) {
				isWithinHome = true;
			}
		}
	}
	//case 4a: current date + 7 days = next month, december
	else if ((*it).getDateStart().year == (currentDate.year + 1)) {
		if ((*it).getDateStart().month == 1) {
			if ((*it).getDateStart().day < (7 - (30 - currentDate.day))) {
				isWithinHome = true;
			}
		}
	}
	//case 5: floating task
	if ((*it).getNumOfDates() == 0) {
		isWithinHome = true;
	}

	if ((*it).doneStatus()){
		isWithinHome = false;
	}

	return isWithinHome;
}

bool Planner::isMissed(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinMissed = false;
	//case 1: passed year
	if ((*it).getDateEnd().year < currentDate.year) {
		isWithinMissed = true;
	}
	//case 2: same year, passed month
	else if ((*it).getDateEnd().year == currentDate.year) {
		if ((*it).getDateEnd().month < currentDate.month) {
			isWithinMissed = true;
		}//case 3: same year, same month, passed day
		else if ((*it).getDateEnd().month == currentDate.month) {
			if ((*it).getDateEnd().day < currentDate.day) {
				isWithinMissed = true;
			}
		}
	}
	
	//case 3: reject floating tasks
	if ((*it).getNumOfDates() == 0) {
			isWithinMissed = false;
		}

	if ((*it).doneStatus()){
		isWithinMissed = false;
	}

	return isWithinMissed;
}

bool Planner::isUpcoming(taskDate currentDate, list<Task>::iterator it){
	bool isWithinUpcoming = true;

	//case 1-4 to check if entry should be within home

	//case 1: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateEnd().month == (currentDate.month)) {
			if ((*it).getDateEnd().day <= (currentDate.day + 7) && (*it).getDateEnd().day >= currentDate.day) {
				if ((*it).getDateEnd().year == currentDate.year) {
					isWithinUpcoming = false;
				}
			}
		}
	}
	//case 2: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateEnd().month == (currentDate.month)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day <= 31 && (*it).getDateEnd().day >= currentDate.day) {
				isWithinUpcoming = false;
			}
		}
	}
	//case 3:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateEnd().month == (currentDate.month + 1)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day < (7 - (30 - currentDate.day))) {
				isWithinUpcoming = false;
			}
		}
	}
	//case 4: current date + 7 days = next month, december
	else if ((*it).getDateEnd().year == (currentDate.year + 1)) {
		if ((*it).getDateEnd().month == 1) {
			if ((*it).getDateEnd().day < (7 - (30 - currentDate.day))) {
				isWithinUpcoming = false;
			}
		}
	}

	//case 1a: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateStart().month == (currentDate.month)) {
			if ((*it).getDateStart().day <= (currentDate.day + 7) && (*it).getDateStart().day >= currentDate.day) {
				if ((*it).getDateStart().year == currentDate.year) {
					isWithinUpcoming = false;
				}
			}
		}
	}
	//case 2a: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateStart().month == (currentDate.month)) {
		if ((*it).getDateStart().year == currentDate.year) {
			if ((*it).getDateStart().day <= 31 && (*it).getDateStart().day >= currentDate.day) {
				isWithinUpcoming = false;
			}
		}
	}
	//case 3a:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateStart().month == (currentDate.month + 1)) {
		if ((*it).getDateStart().year == currentDate.year) {
			if ((*it).getDateStart().day < (7 - (30 - currentDate.day))) {
				isWithinUpcoming = false;
			}
		}
	}
	//case 4a: current date + 7 days = next month, december
	else if ((*it).getDateStart().year == (currentDate.year + 1)) {
		if ((*it).getDateStart().month == 1) {
			if ((*it).getDateStart().day < (7 - (30 - currentDate.day))) {
				isWithinUpcoming = false;
			}
		}
	}
	// case 5-7 to check if entry should be in missed

	//case 5: passed year
	if ((*it).getDateEnd().year < currentDate.year) {
		isWithinUpcoming = false;
	}
	//case 6: same year, passed month
	else if ((*it).getDateEnd().year == currentDate.year) {
		if ((*it).getDateEnd().month < currentDate.month) {
			isWithinUpcoming = false;
		}//case 7: same year, same month, passed day
		else if ((*it).getDateEnd().month == currentDate.month) {
			if ((*it).getDateEnd().day < currentDate.day) {
				isWithinUpcoming = false;
			}
		}
	}

	if ((*it).doneStatus()){
		isWithinUpcoming = false;
	}

	return isWithinUpcoming;
}

