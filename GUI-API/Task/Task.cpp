#include "Task.h"
#include "Log.h"
#include <iostream>
#include <string>
#include <sstream>

const string FATAL_ERROR = "Fatal Error!";
const string ERROR_MESSAGE_INVALID_INPUT = "Invalid format entered! Please re-enter appropriate entry.";
const string UPDATE = "UPDATE";
const string ADD_DETAILS_CASE_0_CALLED = "In addDetails, Case 0 was called";
const string ADD_DETAILS_CASE_0_SUCCESSFUL = "In addDetails, Case 0 was finished successfully";
const string ADD_DETAILS_CASE_1_CALLED = "In addDetails, Case 1 was called";
const string ADD_DETAILS_CASE_1_SUCCESSFUL = "In addDetails, Case 1 was finished successfully";
const string ADD_DETAILS_CASE_2_CALLED = "In addDetails, Case 2 was called";
const string ADD_DETAILS_CASE_2_SUCCESSFUL = "In addDetails, Case 2 was finished successfully";
const string ADD_DETAILS_DESCRIPTION_SUCCESSFUL = "In addDetails(processDescription), Description stored successfully";
const string ADD_DETAILS_DATE_SUCCESSFUL = "In addDetails(processDate), Date stored successfully";
const string ADD_DETAILS_DATE_INVALID = "In addDetails(processDate), Date invalid";
const string ADD_DETAILS_TIME_SUCCESSFUL = "In addDetails(processTime), Time stored successfully";
const string ADD_DETAILS_TIME_INVALID = "In addDetails(processTime), Time invalid";

using namespace std;

/************************************************************************************************

										Initialization

************************************************************************************************/
//Constructor
Task::Task(){
	_timeStart = -1;
	_timeEnd = -1;
	_isImpt = false;
	_isDone = false;
	_isClash = false;
	_numOfDates = 0;
	_numOfTimes = 0;
}

//Destructor
Task::~Task(){
}

/************************************************************************************************

								Task Information Setter Functions

************************************************************************************************/

//Function takes in user input and stores the task details
void Task::addDetails(string details){
	int noOfDelimiters;

	processImportance(details);

	noOfDelimiters = count(details.begin(), details.end(), ';');
	switch (noOfDelimiters){
	case 0:
		process_NoDelimiter(details);
		break;
	case 1:
		process_OneDelimiter(details);
		break;
	case 2:
		process_TwoDelimiter(details);
		break;
	default:
		throw ERROR_MESSAGE_INVALID_INPUT;
	}
}

//For the case when there is only description and no other information fields; stores the task details
void Task::process_NoDelimiter(string details) {
	LogData->addLog(UPDATE, ADD_DETAILS_CASE_0_CALLED);
	_description = details;
	LogData->addLog(UPDATE, ADD_DETAILS_CASE_0_SUCCESSFUL);
}

//For the case when there is description and one other info field (either date or time) separated by a delimiter; stores the task details
void Task::process_OneDelimiter(string details) {
	LogData->addLog(UPDATE, ADD_DETAILS_CASE_1_CALLED);
	processDescription(details);
	if (details.find(" date") != string::npos){
		processDate(details);
	}
	else if (details.find(" time") != string::npos){
		processTime(details);
	}
	else {
		throw ERROR_MESSAGE_INVALID_INPUT;
	}
	LogData->addLog(UPDATE, ADD_DETAILS_CASE_1_SUCCESSFUL);
}

//For the case when there is description and 2 other information fields (date and time) separated by delimiters; stores task details
void Task::process_TwoDelimiter(string details) {
	int semicolonPos;
	string durationInfo, dateInfo, timeInfo;
	LogData->addLog(UPDATE, ADD_DETAILS_CASE_2_CALLED);

	processDescription(details);
	semicolonPos = details.find(';');
	durationInfo = details.substr(0, semicolonPos);
	if (durationInfo.find(" date") != string::npos){
		dateInfo = details.substr(0, semicolonPos);
	}
	else if (durationInfo.find(" time") != string::npos){
		timeInfo = details.substr(0, semicolonPos);
	}
	else {
		throw ERROR_MESSAGE_INVALID_INPUT;
	}
	semicolonPos++;
	if (timeInfo.empty()){
		timeInfo = details.substr(semicolonPos, details.size() - semicolonPos);
	}
	else if (dateInfo.empty()){
		dateInfo = details.substr(semicolonPos, details.size() - semicolonPos);
	}
	processDate(dateInfo);
	processTime(timeInfo);
	LogData->addLog(UPDATE, ADD_DETAILS_CASE_2_SUCCESSFUL);
}

//Checks if task is important and returns the remainder of user input
void Task::processImportance(string& details){
	int hashPosition;
	hashPosition = details.find("#");
	if (hashPosition != string::npos){
		_isImpt = true;
		details = details.substr(0, hashPosition);
	}
}

//stores description into task object and returns the remainder of user input
void Task::processDescription(string& details){
	int descriptionEnd;

	descriptionEnd = details.find_first_of(";");
	_description = details.substr(0, descriptionEnd);
	descriptionEnd++;
	details = details.substr(descriptionEnd, details.size() - descriptionEnd);				//cut out the description part to be left with the date and/or time part
	LogData->addLog(UPDATE, ADD_DETAILS_DESCRIPTION_SUCCESSFUL);
}

void Task::processTwoDates(string startDate, string endDate){

	if (areValidDates(startDate, endDate)){
		storeStartDate(startDate);
		storeEndDate(endDate);
		_numOfDates = 2;
		LogData->addLog(UPDATE, ADD_DETAILS_DATE_SUCCESSFUL);
	}
	else{
		throw ERROR_MESSAGE_INVALID_INPUT;
		LogData->addLog(UPDATE, ADD_DETAILS_DATE_INVALID);
	}
}

void Task::processOneDate(string endDate){
	if (areValidDates(endDate, endDate)){
		storeEndDate(endDate);
		storeStartDate(endDate);
		_numOfDates = 1;
		LogData->addLog(UPDATE, ADD_DETAILS_DATE_SUCCESSFUL);
	}
	else{
		throw ERROR_MESSAGE_INVALID_INPUT;
		LogData->addLog(UPDATE, ADD_DETAILS_DATE_INVALID);
	}
}

//Takes in date related information in a string and stores into the respective variables in Task object
void Task::processDate(string dateInfo){
	string keyword, startDate, endDate, separator;
	int separatorPos;
	istringstream in(dateInfo);

	separatorPos = dateInfo.find("to");			// locate the word to in string
	if (separatorPos != string::npos){
		in >> keyword;
		in >> startDate;
		in >> separator;
		in >> endDate;

		processTwoDates(startDate, endDate);
	}
	else{
		in >> keyword;
		in >> endDate;

		processOneDate(endDate);
	}
}

//Splits the start date string into individual components and stores them in the relevant variables
void Task::storeStartDate(string dateStart){	
	int day, month, year;
	splitDate(dateStart, day, month, year);

	_dateStart.day = day;		
	_dateStart.month = month;
	_dateStart.year = year;
}

//Splits the end date string into individual components and stores them in the relevant variables
void Task::storeEndDate(string dateEnd){
	int day, month, year;
	splitDate(dateEnd, day, month, year);

	_dateEnd.day = day;
	_dateEnd.month = month;
	_dateEnd.year = year;
}

//Takes in time related information in a string and stores into the respective variables in Task object
void Task::processTime(string timeInfo){

	int separatorPos;
	string keyword, timeStart, timeEnd, separator;

	istringstream in(timeInfo);
	separatorPos = timeInfo.find("to");			// locate the word to in string

	if (separatorPos != string::npos){
		in >> keyword;
		in >> timeStart;
		in >> separator;
		in >> timeEnd;

		if (areValidTimes(timeStart, timeEnd)){
			storeStartTime(timeStart);
			storeEndTime(timeEnd);
			_numOfTimes = 2;
			LogData->addLog(UPDATE, ADD_DETAILS_TIME_SUCCESSFUL);
		}
		else {
			LogData->addLog(UPDATE, ADD_DETAILS_TIME_INVALID);
			throw ERROR_MESSAGE_INVALID_INPUT;			
		}
	}
	else{
		in >> keyword;
		in >> timeStart;

		if (areValidTimes(timeStart, timeStart)){
			storeStartTime(timeStart);
			_numOfTimes = 1;
			LogData->addLog(UPDATE, ADD_DETAILS_TIME_SUCCESSFUL);
		}
		else {
			LogData->addLog(UPDATE, ADD_DETAILS_TIME_INVALID);
			throw ERROR_MESSAGE_INVALID_INPUT;			
		}
	}
}

//Takes in start time as a string and converts it to integer before storing into relevant attributes in Task object
void Task::storeStartTime(string time) {

	try {
		_timeStart = stoi(time);
	}
	catch (invalid_argument& error){
		throw ERROR_MESSAGE_INVALID_INPUT;
	}
}

//Takes in end time as a string and converts it to integer before storing into relevant attributes in Task object
void Task::storeEndTime(string time) {
	try {
		_timeEnd = stoi(time);
	}
	catch (invalid_argument& error){
		throw ERROR_MESSAGE_INVALID_INPUT;
	}
}

//Stores a unique ID number that is created by the Planner class
void Task::storeIdNumber(int num){
	_idNumber = num;
}

//Marks a particular task as done
void Task::markIsDoneAsTrue(){
	_isDone = true;
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

//@author A0111361Y
bool Task::doneStatus(){
	return _isDone;
}

/************************************************************************************************

										Recur function

************************************************************************************************/

void Task::recurTask(string details){
	string frequency, taskDetails;
	int numOfRecurrence, semicolonPos;
	char delimiter;
	Task *recTaskPtr;

	istringstream in(details);
	in >> frequency;						//daily, weekly, monthly or yearly
	in >> numOfRecurrence;					//no of times to recur
	
	semicolonPos = details.find_first_of(";");
	semicolonPos++;

	details = details.substr(semicolonPos, details.size() - semicolonPos);		//to extract out relevant details for task
	
	for (int i = 1; i <= numOfRecurrence; i++){
		recTaskPtr = new Task;
		(*recTaskPtr).addDetails(details);
		_recurringTasks.push_back(*recTaskPtr);
		delete recTaskPtr;
		recTaskPtr = NULL;
		details = modifyDetails(frequency, details);
	}
}

string Task::modifyDetails(string frequency, string details){
	int index, numOfDates;
	string keyword, startDate, endDate, separator, dateInfo, newDateInfo;
	ostringstream updatedInfo;

	dateInfo = extractDateInfo(details);
	numOfDates = extractDateInfoFields(dateInfo, keyword, startDate, endDate, separator);
	
	switch (numOfDates){
	case 1:
		endDate = modifyDate(endDate, frequency);
		updatedInfo << " " << keyword << " " << endDate;
		newDateInfo = updatedInfo.str();
		details = insertNewDateInfo(details, newDateInfo);
		break;

	case 2:
		startDate = modifyDate(startDate, frequency);
		endDate = modifyDate(endDate, frequency);
		updatedInfo << " " << keyword << " " << startDate << " " << separator << " " << endDate;
		newDateInfo = updatedInfo.str();
		details = insertNewDateInfo(details, newDateInfo);
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
	
	if (month == 2){						//case when it is Feb 28th
		if (day == 28){
			day = 1;
			month++;
		}
	}
	else if (is31DayMonth(month)){
		if (day == 31){						//case when it is
			if (month == 12){				//31st Dec
				day = 1;
				month = 1;
				year++;
			}
			else{							//case when it is 31st but not Dec
				day = 1;
				month++;
			}
		}
		else{								//case when it is month with 31 days and it is any day from 1-30
			day++;
		}
	}
	else{
		if (day == 30){						//case when it is month with 30 days and day is 30th
			day = 1;
			month++;
		}
		else{								//case when it is month with 30 days and day is 1-29
			day++;
		}
	}

	mergeDate(date, day, month, year);
	return date;
}

string Task::processWeeklyRecur(string date){

	for (int i = 1; i <= 7; i++){				//since each week is 7 days, just loop processDailyRecur 7 times
		date = processDailyRecur(date);
	}

	return date;
}

string Task::processMonthlyRecur(string date){
	int day, month, year;
	splitDate(date, day, month, year);
	
	if (month == 12){
		month = 1;
		year++;
	}
	else{
		month++;
	}

	mergeDate(date, day, month, year);
	
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
	try {
		day = stoi(endDate.substr(0, 2));
		month = stoi(endDate.substr(2, 2));
		year = stoi(endDate.substr(4, 2));
	}
	catch (invalid_argument& error){
		throw ERROR_MESSAGE_INVALID_INPUT;
	}

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
	//	index++;
	details = details.substr(0, index);

	return details;
}

//@author A0111361Y
void Task::markClashAsTrue(){
	_isClash = true;
}

//@author A0111361Y
void Task::markClashAsFalse(){
	_isClash = false;
}

//@author A0111361Y
bool Task::clashStatus(){
	if (_isClash == true){
		return true;
	}
	else {
		return false;
	}
}

/************************************************************************************************

									Checker Functions

************************************************************************************************/

bool Task::areValidDates(string startDate, string endDate){
	bool areDatesValid = false;	
	
	if (correctDateLength(startDate) && correctDateLength(endDate)){
		if (isValidDate(startDate) && isValidDate(endDate)){
			if (startDateBeforeEndDate(startDate, endDate)){
				areDatesValid = true;
			}
		}
	}

	return areDatesValid;
}

bool Task::correctDateLength(string date){
	bool isCorrectDateLength = false;

	if (date.size() == 6){
		isCorrectDateLength = true;
	}
	return isCorrectDateLength;
}

bool Task::startDateBeforeEndDate(string startDate, string endDate) {
	bool isStartBeforeEnd = true;
	int startDay, startMonth, startYear;
	int endDay, endMonth, endYear;

	splitDate(startDate, startDay, startMonth, startYear);
	splitDate(endDate, endDay, endMonth, endYear);

	if (startYear > endYear){
		isStartBeforeEnd = false;
	}
	else if (startMonth > endMonth){
		isStartBeforeEnd = false;
	}
	else if (startDay > endDay){
		isStartBeforeEnd = false;
	}

	return isStartBeforeEnd;
}

bool Task::isValidDate(string date) {
	bool dateIsValid=false;
	int day, month, year;

	splitDate(date, day, month, year);


	if (day >= 1 && day <= 31){
		if (month >= 1 && month <= 12){
			dateIsValid = true;
		}
	}

	return dateIsValid;
}

bool Task::areValidTimes(string timeStart, string timeEnd){
	bool areTimesValid = false;
	int intTimeStart, intTimeEnd;

	try {
		intTimeStart = stoi(timeStart);
		intTimeEnd = stoi(timeEnd);
	}
	catch (invalid_argument& error){
		throw ERROR_MESSAGE_INVALID_INPUT;
	}

	if (isValidTime(intTimeStart) && (isValidTime(intTimeEnd))){
		if (startTimeBeforeEndTime(intTimeStart, intTimeEnd)){
			areTimesValid = true;
		}
	}

	return areTimesValid;
}

bool Task::isValidTime(int time){
	bool timeIsValid = false;

	if (time >= 0 && time <= 2359){
		timeIsValid = true;
	}

	return timeIsValid;
}

bool Task::startTimeBeforeEndTime(int startTime, int endTime){
	bool isStartTimeBeforeEndTime = false;

	if (startTime <= endTime){
		isStartTimeBeforeEndTime = true;
	}

	return isStartTimeBeforeEndTime;
}

bool Task::areDatesTheSame(taskDate Date1, taskDate Date2){
	bool same = true;

	if (Date1.day != Date2.day){
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

bool Task::is31DayMonth(int month){
	bool is31DayMonth = false;

	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
		is31DayMonth = true;
	}

	return is31DayMonth;
}

/************************************************************************************************

											Search function

************************************************************************************************/

//Checks if the target word is present in the task description
bool Task::isSearchTargetPresent(string target){
	LogData->addLog(UPDATE, "In isSearchTargetPresent, search initiated");
	bool isFound = true;
	string targetWithUpperCase = target, targetWithLowerCase = target;
	targetWithUpperCase[0] = toupper(targetWithUpperCase[0]);
	targetWithLowerCase[0] = tolower(targetWithLowerCase[0]);

	if ((_description.find(target) == string::npos) &&
		(_description.find(targetWithUpperCase) == string::npos) &&		////for search to include the target with first letter in upper case
		(_description.find(targetWithLowerCase) == string::npos)){		//for search to include the target with first letter in lower case
		isFound = false;
	}

	LogData->addLog(UPDATE, "In isSearchTargetPresent, search completed");
	return isFound;
}