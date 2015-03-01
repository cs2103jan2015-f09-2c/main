#include "Task.h"
#include <iostream>
#include <string>

using namespace std;

//Constructor
Task::Task(){
	_isImpt = false;
}

//Destrcutor
Task::~Task(){
}

//Function takes in user input and stores the task details
void Task::addDetails(string details){
	int index, newIndex, noOfDelimiters;
	string dateInfo, timeInfo;
	char delimiter;

	index = details.find("#");
	if (index != string::npos){
		_isImpt = true;
		details = details.substr(0, index);
	}
	
	noOfDelimiters = count(details.begin(), details.end(), ';');

	switch (noOfDelimiters){
	case 0:
		_description = details;
	case 1:
		index = details.find_first_of(";");
		_description = details.substr(0, index);
		index = index + 1;
		details = details.substr(index, details.size() - index);
		delimiter = details.at(0);
		if (delimiter == 'd'){
			details = details.substr(1, details.size()-1);
			processDate(details);
		}
		else{
			details = details.substr(1, details.size() - 1);
			processTime(details);
		}
	case 2:
		index = details.find_first_of(";");
		_description = details.substr(0, index);
		index = index + 2;
		newIndex = details.find_first_of(";", index);
		dateInfo = details.substr(index, newIndex - index);
		processDate(dateInfo);
		newIndex = newIndex + 2;
		timeInfo = details.substr(newIndex, details.size() - newIndex);
		processTime(timeInfo);
	}
}

//Takes in date related information in a string and stores into the respective variables in Task object
void Task::processDate(string dateInfo){
	//need to confirm
	_dateStart.day = 02;
	_dateStart.month = 03;
	_dateStart.year = 15;

	_dateEnd.day = 03;
	_dateEnd.month = 03;
	_dateEnd.year = 15;
}

//Takes in time related information in a string and stores into the respective variables in Task object
void Task::processTime(string timeInfo){
	//need to confirm
	_timeStart.hour = 15;
	_timeStart.min = 30;

	_timeEnd.hour = 16;
	_timeEnd.min = 30;
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
taskTime Task::getTimeStart(){
	return _timeStart;
}

//Returns end time of task
taskTime Task::getTimeEnd(){
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
bool Task::isImpt(){
	return _isImpt;
}
