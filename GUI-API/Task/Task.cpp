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
	_isClash = false;
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
		storeStartDate(endDate);
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

list<Task> Task::getRecurringTasks(){
	return _recurringTasks;
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





//******************************************************************************************************************************



void Task::recurTask(string details){
	string frequency, taskDetails;
	int numOfRecurrence, index;
	char delimiter;
	Task *recTaskPtr;

	istringstream in(details);
	in >> frequency;						//daily, weekly, monthly or yearly
	in >> numOfRecurrence;					//no of times to recur
	
	index = details.find_first_of(";");
	index++;

	details = details.substr(index, details.size() - index);		//to extract out relevant details for task
	
	for (int i = 1; i <= numOfRecurrence; i++){
		recTaskPtr = new Task;
		(*recTaskPtr).addDetails(details);
		_recurringTasks.push_back(*recTaskPtr);
		delete recTaskPtr;
		recTaskPtr = NULL;
		details = modifyDetails(i, frequency, details);
	}

}

string Task::modifyDetails(int n, string frequency, string details){
	int index, numOfDates;
	string keyword, startDate, endDate, separator, dateInfo, newDate;
	ostringstream newDateInfo;

	dateInfo = extractDateInfo(details);
	numOfDates = extractDateInfoFields(dateInfo, keyword, startDate, endDate, separator);
	
	switch (numOfDates){
	case 1:
		endDate = modifyDate(endDate, frequency);
		newDateInfo << keyword << " " << endDate;
		newDate = newDateInfo.str();
		details = insertNewDateInfo(details, newDate);
		break;

	case 2:
//		modifyStartAndEndDate(startDate, endDate);
//		modifyDate(start,freq)
//		modifyDate(end,freq)

		break;
	default:
		break;
	}
	
	return details;
}

string Task::insertNewDateInfo(string details, string newDate){
	int indexDateInfoStart, indexDateInfoEnd;
	indexDateInfoStart = details.find_first_of(";");
	indexDateInfoStart++;
	indexDateInfoEnd = details.find_first_of(";", indexDateInfoStart);
	details.replace(indexDateInfoStart, indexDateInfoEnd - indexDateInfoStart, "");		//deleting old date info
	details.insert(indexDateInfoStart, newDate);

	return details;
}

string Task::modifyDate(string date, string frequency){
	string newDate;

	if (frequency == "daily" || frequency == "Daily"){
		newDate = processDailyRecur(date);
	}
	else if (frequency == "weekly" || frequency == "Weekly"){
		newDate = processWeeklyRecur(date);
	}
	else if (frequency == "monthly" || frequency == "Monthly"){
		newDate = processMonthlyRecur(date);
	}
	else if (frequency == "yearly" || frequency == "Yearly"){
		newDate = processYearlyRecur(date);
	}
	
	return newDate;
}

string Task::processDailyRecur(string date){
	int day, month, year;
	splitDate(date, day, month, year);
	
	return date;
}

string Task::processWeeklyRecur(string date){
	int day, month, year;
	splitDate(date, day, month, year);

	return date;
}

string Task::processMonthlyRecur(string date){
	int day, month, year;
	splitDate(date, day, month, year);

	return date;
}

string Task::processYearlyRecur(string date){
	int day, month, year;
	splitDate(date, day, month, year);

	if (year+1 != 100){			//to ensure year is a 2 digit number
		year++;
	}

	mergeDate(date, day, month, year);

	return date;
}

void Task::splitDate(string endDate, int& day, int& month, int& year){
	day = stoi(endDate.substr(0, 2));
	month = stoi(endDate.substr(2, 2));
	year = stoi(endDate.substr(4, 2));
}

void Task::mergeDate(string& date, int day, int month, int year){
	ostringstream mergedDate;
	if (day < 10){
		mergedDate << "0" << day;
	}
	else{
		mergedDate << day;
	}

	if (month < 10){
		mergedDate << "0" << month;
	}
	else{
		mergedDate << month;
	}

	if (year < 10){
		mergedDate << "0" << year;
	}
	else{
		mergedDate << year;
	}

	date = mergedDate.str();
}

int Task::extractDateInfoFields(string dateInfo, string& keyword, string& startDate, string& endDate, string& separator){
	int numOfDates, index;
	istringstream in(dateInfo);
	index = dateInfo.find("to");			// locate the word to in string
	
	if (index != string::npos){
		in >> keyword;
		in >> startDate;
		in >> separator;
		in >> endDate;
		numOfDates = 2;
	}
	else{
		in >> keyword;
		in >> endDate;
		storeEndDate(endDate);
		numOfDates = 1;
	}

	return numOfDates;
}

string Task::extractDateInfo(string details){
	int index;

	index = details.find("date");
	details = details.substr(index, details.size() - index);

	//get rid of #impt if exists
	index = details.find("#");						
	if (index != string::npos){
		details = details.substr(0, index);
	}

	//get rid of time if exists
	index = details.find_first_of(";");			//find first delimiter
	index++;
	details = details.substr(0, details.size() - index);

	return details;
}

bool Task::areDatesTheSame(taskDate Date1, taskDate Date2){
	bool same = true;
	if (Date1.day!=Date2.day){
		same = false;
	}
	if (Date1.month != Date2.month){
		same = false;
	}
	if (Date1.year != Date2.year){
		same = false;
	}
	
	return same;
}

void Task::markClashAsTrue(){
	_isClash = true;
}

bool Task::clashStatus(){
	if (_isClash == true){
		return true;
	}
	else return false;
}

/*
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
*/