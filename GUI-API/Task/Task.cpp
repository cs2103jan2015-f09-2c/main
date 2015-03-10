#include "Task.h"
#include <iostream>
#include <string>

using namespace std;

//Constructor
Task::Task(){
	_timeStart = -1;
	_timeEnd = -1;
	_isImpt = false;
	_numOfDates = 0;
	_numOfTimes = 0;
}

//Destrcutor
Task::~Task(){
}

//Function takes in user input and stores the task details
void Task::addDetails(string details){
	int index, noOfDelimiters;
	string dateInfo, timeInfo;

	details = processImportance(details);

	noOfDelimiters = count(details.begin(), details.end(), ';');
	
	switch (noOfDelimiters){
	case 0:
		_description = details;
		break;
	case 1:
		details = processDescription(details);
		if (details.find("date") != string::npos){
			processDate(details);
		}
		else{
			processTime(details);
		}
		break;
	case 2:
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
	return details;
}

//Takes in date related information in a string and stores into the respective variables in Task object
void Task::processDate(string dateInfo){
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
}

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
	string timeStart, timeEnd;

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
		_timeStart = stoi(timeStart);
		_numOfTimes = 1;
	}
}

//Checks if the target word is present in the task description
bool Task::isSearchTargetPresent(string target){
	bool isFound = true;
	if (_description.find(target) == string::npos){
		isFound = false;
	}
	return isFound;
}

//Returns task description
string Task::getDescription(){
	return _description;
}

//Returns start time of task
int Task::getTimeStart(){
	return _timeStart;
}

//Returns end time of task
int Task::getTimeEnd(){
	return _timeEnd;
}

//Return start date of task
taskDate Task::getDateStart(){
	return _dateStart;
}

//Return end date of task
taskDate Task::getDateEnd(){
	return _dateEnd;
}

//Checks if task is marked as important by user
bool Task::getImportance(){
	return _isImpt;
}

//Stores a unique ID number that is created by the K5 planner class
void Task::storeIdNumber(int num){
	_idNumber = num;
}

//Returns unique ID number
int Task::getIdNumber(){
	return _idNumber;
}

//Returns the number of dates user has input for the particular task. i.e. if user has input both start and end date then function 
//will return 2
int Task::getNumOfDates(){
	return _numOfDates;
}

//Returns the number of timings user has input for the particular task. i.e. if user has input both start and end time then function 
//will return 2
int Task::getNumOfTimes(){
	return _numOfTimes;
}