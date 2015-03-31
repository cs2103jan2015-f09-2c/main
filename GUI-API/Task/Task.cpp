#include "Task.h"
#include "Log.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/************************************************************************************************

										Initialization

************************************************************************************************/

Task::Task(){
	_timeStart = -1;
	_timeEnd = -1;
	_isImpt = false;
	_isDone = false;
	_numOfDates = 0;
	_numOfTimes = 0;
}

Task::~Task(){
}

/************************************************************************************************

								Task Information Setter Functions

************************************************************************************************/

//Function takes in user input and stores the task details
void Task::addDetails(string details){
	int index, noOfDelimiters;
	string dateInfo, timeInfo;

	details = processImportance(details);

	noOfDelimiters = count(details.begin(), details.end(), ';');
	switch (noOfDelimiters){
	case 0:
		LogData->addLog("UPDATE", "In addDetails, Case 0 was called");
		_description = details;
		LogData->addLog("UPDATE", "In addDetails, Case 0 was finished successfully");
		break;
	case 1:
		LogData->addLog("UPDATE", "In addDetails, Case 1 was called");
		details = processDescription(details);
		if (details.find("date") != string::npos){
			processDate(details);
		}
		else if (details.find("time") != string::npos){
			processTime(details);
		}
		else if (details.find("recur") != string::npos){
		//	processRecur(details);
		}
		LogData->addLog("UPDATE", "In addDetails, Case 1 was finished successfully");
		break;
	case 2:
		LogData->addLog("UPDATE", "In addDetails, Case 2 was called");
		details = processDescription(details);
		index = details.find(';');
		if (details.substr(0, index).find("date") != string::npos){
			dateInfo = details.substr(0, index);
		}
		else{
			timeInfo = details.substr(0, index);
		}
		index = index + 1;
		if (timeInfo.empty()){
			timeInfo = details.substr(index, details.size() - index);
		}
		else{
			dateInfo = details.substr(index, details.size() - index);
		}
		processDate(dateInfo);
		processTime(timeInfo);
		LogData->addLog("UPDATE", "In addDetails, Case 2 was finished successfully");
		break;
	default:
		cout << "fatal error!" << endl;
	}
}

//Checks if task is important and returns the remainder of user input
string Task::processImportance(string details){
	int index;
	index = details.find("#");						//to check if task is labelled important
	if (index != string::npos){
		_isImpt = true;
		details = details.substr(0, index);
	}
	return details;
}

//stores description into task object and returns the remainder of user input
string Task::processDescription(string details){
	int index;

	index = details.find_first_of(";");
	_description = details.substr(0, index);
	index = index + 1;
	details = details.substr(index, details.size() - index);				//cut out the description part to be left with the date and/or time part
	LogData->addLog("UPDATE", "In addDetails(processDescription), Description stored successfully");
	return details;

}

//Takes in date related information in a string and stores into the respective variables in Task object
void Task::processDate(string dateInfo){
	string keyword, startDate, endDate, separator;
	int index;
	istringstream in(dateInfo);

	index = dateInfo.find("to");			// locate the word to in string
	if (index != string::npos){
		in >> keyword;
		in >> startDate;
		in >> separator;
		in >> endDate;
		storeStartDate(startDate);
		storeEndDate(endDate);
		_numOfDates = 2;
	}
	else{
		in >> keyword;
		in >> endDate;
		storeEndDate(endDate);
		_numOfDates = 1;
	}

	
	/*
	int index;
	string dateStart, dateEnd;

	dateInfo.replace(0, 6, "");				//get rid of the word date at the start of the string

	index = dateInfo.find("to");			// locate the word to in string

	if (index != string::npos){
		dateStart = dateInfo.substr(0, index - 1);
		index = index + 3;
		dateEnd = dateInfo.substr(index, dateInfo.size() - index);
		storeStartDate(dateStart);
		storeEndDate(dateEnd);
		_numOfDates = 2;
	}
	else{
		storeEndDate(dateInfo);
		_numOfDates = 1;
	}
	*/

	LogData->addLog("UPDATE", "In addDetails(processDate), Date stored successfully");
}

/*
void Task::processRecur(string recurInfo){
	recurInfo.replace(0, 7, "");			//get rid of the word recur at the start of the string

}
*/

//Splits the start date string into individual components and stores them in the relevant variables
void Task::storeStartDate(string dateStart){
	string day, month, year;
	day = dateStart.substr(0, 2);					// These are all in string form
	month = dateStart.substr(2, 2);
	year = dateStart.substr(4, 2);

	_dateStart.day = stoi(day);						// To convert the strings to integer
	_dateStart.month = stoi(month);
	_dateStart.year = stoi(year);
}

//Splits the end date string into individual components and stores them in the relevant variables
void Task::storeEndDate(string dateEnd){
	string day, month, year;
	day = dateEnd.substr(0, 2);						// These are all in string form
	month = dateEnd.substr(2, 2);
	year = dateEnd.substr(4, 2);

	_dateEnd.day = stoi(day);						// To convert the strings to integer
	_dateEnd.month = stoi(month);
	_dateEnd.year = stoi(year);
}

//Takes in time related information in a string and stores into the respective variables in Task object
void Task::processTime(string timeInfo){

	int index;
	string keyword, timeStart, timeEnd, separator;

	istringstream in(timeInfo);
	index = timeInfo.find("to");			// locate the word to in string

	if (index != string::npos){
		in >> keyword;
		in >> timeStart;
		in >> separator;
		in >> timeEnd;

		_timeStart = stoi(timeStart);
		_timeEnd = stoi(timeEnd);
		_numOfTimes = 2;
	}
	else{
		in >> keyword;
		in >> timeStart;
		_timeStart = stoi(timeStart);
		_numOfTimes = 1;
	}

	/*
	timeInfo.replace(0, 6, "");				//get rid of the word time at the start of the string

	index = timeInfo.find("to");			// locate the word to in string

	if (index != string::npos){
		timeStart = timeInfo.substr(0, index - 1);
		index = index + 3;
		timeEnd = timeInfo.substr(index, timeInfo.size() - index);
		_timeStart = stoi(timeStart);
		_timeEnd = stoi(timeEnd);
		_numOfTimes = 2;
	}
	else{
		_timeStart = stoi(timeInfo);
		_numOfTimes = 1;
	}
	*/
	LogData->addLog("UPDATE", "In addDetails(processTime), Time stored successfully");
}

//Stores a unique ID number that is created by the Planner class
void Task::storeIdNumber(int num){
	_idNumber = num;
}

/************************************************************************************************

								Task Information Getter Functions

************************************************************************************************/

string Task::getDescription(){
	return _description;
}

int Task::getTimeStart(){
	return _timeStart;
}

int Task::getTimeEnd(){
	return _timeEnd;
}

taskDate Task::getDateStart(){
	return _dateStart;
}

taskDate Task::getDateEnd(){
	return _dateEnd;
}

bool Task::getImportance(){
	return _isImpt;
}

int Task::getIdNumber(){
	return _idNumber;
}

int Task::getNumOfDates(){
	return _numOfDates;
}

int Task::getNumOfTimes(){
	return _numOfTimes;
}

/************************************************************************************************

Search function

************************************************************************************************/

//Checks if the target word is present in the task description
bool Task::isSearchTargetPresent(string target){
	LogData->addLog("UPDATE", "In isSearchTargetPresent, search initiated");
	bool isFound = true;
	string targetWithUpperCase = target, targetWithLowerCase = target;
	targetWithUpperCase[0] = toupper(targetWithUpperCase[0]);
	targetWithLowerCase[0] = tolower(targetWithLowerCase[0]);

	if (_description.find(target) == string::npos){
		if (_description.find(targetWithUpperCase) == string::npos){			//for search to include the target with first letter in upper case
			if (_description.find(targetWithLowerCase) == string::npos){		//for search to include the target with first letter in upper case
				isFound = false;
			}
		}
	}

	LogData->addLog("UPDATE", "In isSearchTargetPresent, search completed");
	return isFound;
}



void Task::markIsDoneAsTrue(){
	_isDone = true;
}

bool Task::doneStatus(){
	return _isDone;
}