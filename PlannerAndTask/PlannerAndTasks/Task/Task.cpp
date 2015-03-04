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
	cout << noOfDelimiters << endl;
	switch (noOfDelimiters){
		case 0:
			_description = details;
			break;
		case 1:
			index = details.find_first_of(";");
			_description = details.substr(0, index);
			index = index + 1;
			details = details.substr(index, details.size() - index);			//cut out the description part to be left with the date or time part

			if (details.find("date") != string::npos){
				processDate(details);
				}
			else{
				processTime(details);
				}
			break;
		case 2:
			index = details.find_first_of(";");
			_description = details.substr(0, index);
			index = index + 1;
			details = details.substr(index, details.size() - index);			//cut out the description part to be left with the date or time part

			index = details.find(';');
			dateInfo = details.substr(0, index);								//extract out the date info
			index = index + 1;
			timeInfo = details.substr(index, details.size() - index);			//extract out the time info

			processDate(dateInfo);

			processTime(timeInfo);
			break;
		default:
			cout << "fatal error!" << endl;
		}
	}

//Takes in date related information in a string and stores into the respective variables in Task object
void Task::processDate(string dateInfo){
	int index;
	string dateStart, dateEnd;

	dateInfo.replace(0, 6, "");				//get rid of the word date at the start of the string

	index = dateInfo.find("to");			// locate the word to in string

	if (index != string::npos){
		dateStart = dateInfo.substr(0, index);
		index = index + 2;
		dateEnd = dateInfo.substr(index, dateInfo.size() - index);
		storeStartDate(dateStart);
		storeEndDate(dateEnd);
		}
	else{
		storeEndDate(dateInfo);
		}
	}

void Task::storeStartDate(string dateStart){
	string day, month, year;
	day = dateStart.substr(0, 2);
	month = dateStart.substr(2, 2);
	year = dateStart.substr(4, 2);

	_dateStart.day = stoi(day);
	_dateStart.month = stoi(month);
	_dateStart.year = stoi(year);
	}

void Task::storeEndDate(string dateEnd){
	string day, month, year;
	day = dateEnd.substr(0, 2);
	month = dateEnd.substr(2, 2);
	year = dateEnd.substr(4, 2);

	_dateEnd.day = stoi(day);
	_dateEnd.month = stoi(month);
	_dateEnd.year = stoi(year);
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
