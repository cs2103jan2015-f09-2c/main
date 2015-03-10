#include "Planner.h"
#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;

//Functions that edit the HomeONLY
void Planner::addTask(Task newTask){
	//create new task
	int id = getIdOfLastEntry(); // use static to actually create id
	newTask.storeIdNumber(id);

	//check where to slot
	list<Task>::iterator iter;
	for (iter = Home.begin(); iter != Home.end(); ++iter){
		if (newTask.getDateStart().year <= (*iter).getDateStart().year)
			if (newTask.getDateStart().month < (*iter).getDateStart().month)
				break;
			else
				if (newTask.getDateStart().month == (*iter).getDateStart().month)
					if (newTask.getDateStart().day < (*iter).getDateStart().day)
						break;
					else
						if (newTask.getDateStart().day == (*iter).getDateStart().day){
							if (newTask.getTimeStart() <= (*iter).getTimeStart())
								break;
							}
		}


	Home.insert(iter, newTask);

	lastEntry.lastCommand = "add";
	lastEntry.lastTask = newTask;

	generateAllOtherList();



	//add in the details
	//newTask = content; // i dont know if this correct
	//check time and date
	//taskTime StartTime = newTask._timeStart;
	//taskTime EndTime = newTask._timeEnd;
	//taskDate StartDate = newTask._dateStart;
	//taskDate EndDate = newTask._dateEnd;
	//check for clash
	//bool clash = false;
	//clash=checkForClash(StartTime, EndTime, StartDate, EndDate);
	//if no clash,
	//find spot to enter
	/*int index;
	taskTime startTime, endTime;
	taskDate startDate, endDate;
	startTime = content.getTimeStart();
	endTime = content.getTimeEnd();
	startDate = content.getDateStart();
	endDate = content.getDateEnd();
	if (!clash){
	index = findIndexToSlotIn(startTime, endTime, startDate, endDate);
	}*/

	//enter in to the list
	//list<Task>::iterator it = allTaskList.begin();
	//for (int i = 0; i < index; i++){
	///it++;
	//}
	//allTaskList.insert(it, newTask);
	//generate next7daysList, upcomingList, missedList,
	//generate_next7DaysList();
	//generate_upcomingList();
	//generate_missedList();
	//update the undoData, lastEntry Data Structure
	}

string Planner::toString(string nameOfList){
	//convert the list to a string and return
	string finalString;
	if (nameOfList == "Home"){
		finalString = HomeToString();
		return finalString;
		}
	else if (nameOfList == "Upcoming"){
		finalString = upcomingListToString();
		return finalString;
		}
	else if (nameOfList == "Missed"){
		finalString = searchListToString(); // remember to change this back to missedListToString
		return finalString;
		}
	else if (nameOfList == "searchList"){
		finalString = searchListToString();
		return finalString;
		}
	}

int Planner::getIdOfLastEntry(void){

	int n;

	static int idGeneratror;
	if (Home.empty()){
		idGeneratror = 10001;
		}
	else idGeneratror++;
	return idGeneratror;
	}

void Planner::deleteTask(int serialNumber, string nameOfList){
	int idNumber;
	list<Task> ::iterator iter;
	iter = Home.begin();
	if (nameOfList == "Home"){
		for (int i = 1; i != serialNumber; i++){
			iter++;
			}
		idNumber = (*iter).getIdNumber();
		deleteIndex(idNumber);
		}
	else cout << "error! name of list is invalid" << endl;

	}

void Planner::deleteIndex(int idNumber){
	list<Task> ::iterator iter1, iter2;
	iter1 = Home.begin();
	for (iter1 = Home.begin(); iter1 != Home.end(); ++iter1){
		if ((*iter1).getIdNumber() == idNumber){
			iter2 = iter1;
			}
		}
	lastEntry.lastTask = *iter2;
	lastEntry.lastCommand = "delete";
	Home.erase(iter2);

	generateAllOtherList();



	}

void Planner::undo(void){
	if (lastEntry.lastCommand == "add"){
		int lastEntryID = getIdOfLastEntry() - 1;
		deleteIndex(lastEntryID);
		}
	else if (lastEntry.lastCommand == "delete"){
		addTask(lastEntry.lastTask);
		}

	generateAllOtherList();

	}

void Planner::clear(void){
	Home.clear();
	generateAllOtherList();
	}

void Planner::editTask(int serialNumber, string nameOfList, string input){
	Task newTask;
	newTask.addDetails(input);
	deleteTask(serialNumber, nameOfList);
	addTask(newTask);
	generateAllOtherList();
	}

void Planner::save(string fileName){
	ofstream write(fileName);
	string allTasks;
	allTasks = Planner::toString("Home");
	write << allTasks;
	write.close();
	}

string Planner::HomeToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = Home.begin();
	int serialNumber = 1;
	if (!Home.empty()){
		for (it = Home.begin(); it != Home.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";
			
//			if ((*it).getDateStart().day != -1 && (*it).getDateEnd().day != -1) {
				out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
//			}
			// don't edit this part. its not finished. going to add more

			if ((*it).getTimeEnd() != -1) {
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
			}
			else{
				if ((*it).getTimeStart() != -1){
					out << (*it).getTimeStart();
				}
			}
			out << " " << (*it).getIdNumber();			//remember to remove

			if ((*it).isImpt()){
				out << " #impt";
				}
			out << "\r\n";
			serialNumber++;
			}
		}
	else out << "The list is empty!" << endl;

	return out.str();
	}

string Planner::next7DaystoString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = next7DaysList.begin();
	int serialNumber = 1;
	if (!next7DaysList.empty()){
		for (it = next7DaysList.begin(); it != next7DaysList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";
			//			if ((*it).getDateStart().day != -1) {
			out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
			out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
			//			}
			//			if ((*it).getTimeStart() != -1) {
			out << (*it).getTimeStart() << " to ";
			out << (*it).getTimeEnd();
			//			}
			out << " " << (*it).getIdNumber();			//remember to remove

			if ((*it).isImpt()){
				out << " #impt";
				}
			out << "\r\n";
			serialNumber++;
			}
		}
	else out << "The list is empty!" << endl;

	return out.str();
	}

string Planner::upcomingListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = UpcomingList.begin();
	int serialNumber = 1;
	if (!UpcomingList.empty()){
		for (it = UpcomingList.begin(); it != UpcomingList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";
			//			if ((*it).getDateStart().day != -1) {
			out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
			out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
			//			}
			//			if ((*it).getTimeStart() != -1) {
			out << (*it).getTimeStart() << " to ";
			out << (*it).getTimeEnd();
			//			}
			out << " " << (*it).getIdNumber();			//remember to remove

			if ((*it).isImpt()){
				out << " #impt";
				}
			out << "\r\n";
			serialNumber++;
			}
		}
	else out << "The list is empty!" << endl;

	return out.str();
	}

string Planner::missedListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = MissedList.begin();
	int serialNumber = 1;
	if (!MissedList.empty()){
		for (it = MissedList.begin(); it != MissedList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";
			//			if ((*it).getDateStart().day != -1) {
			out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
			out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
			//			}
			//			if ((*it).getTimeStart() != -1) {
			out << (*it).getTimeStart() << " to ";
			out << (*it).getTimeEnd();
			//			}
			out << " " << (*it).getIdNumber();			//remember to remove

			if ((*it).isImpt()){
				out << " #impt";
				}
			out << "\r\n";
			serialNumber++;
			}
		}
	else out << "The list is empty!" << endl;

	return out.str();
	}

string Planner::searchListToString(void){
	
	ostringstream out;
	list<Task> ::iterator it;
	it = searchList.begin();
	int serialNumber = 1;
	if (!searchList.empty()){
		out << "SEARCH RESULTS : \r\n";
		for (it = searchList.begin(); it != searchList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";
			//			if ((*it).getDateStart().day != -1) {
			out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
			out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
			//			}
			//			if ((*it).getTimeStart() != -1) {
			out << (*it).getTimeStart() << " to ";
			out << (*it).getTimeEnd();
			//			}
			out << " " << (*it).getIdNumber();			//remember to remove

			if ((*it).isImpt()){
				out << " #impt";
				}
			out << "\r\n";
			serialNumber++;
			}
		}
	else out << "Sorry, nothing matched your search target :( \r\n" << endl;

	return out.str();
	}

void Planner::generateAllOtherList(void){
	next7DaysList.clear();
	MissedList.clear();
	UpcomingList.clear();
	generateNext7DaysList();
	generateMissedList();
	generateUpcomingList();
	}

void Planner::generateNext7DaysList(void){
	list<Task> ::iterator iter;

	for (iter = Home.begin(); iter != Home.end(); ++iter){
		// if item falls in category
		next7DaysList.push_back(*iter);
		}

	}

void Planner::generateUpcomingList(void){
	list<Task> ::iterator iter;
	Task tempTask;

	for (iter = Home.begin(); iter != Home.end(); ++iter){
		// if item falls in category
		tempTask = *iter;
		UpcomingList.push_back(tempTask);
		}
	}

void Planner::generateMissedList(void){
	list<Task> ::iterator iter;

	for (iter = Home.begin(); iter != Home.end(); ++iter){
		// if item falls in category
		MissedList.push_back(*iter);
		}
	}

void Planner::generateSearchList(string target){
	list<Task> ::iterator iter;
	Task tempTask;
	searchList.clear();
	for (iter = Home.begin(); iter != Home.end(); ++iter){
		tempTask = *iter;
		if (tempTask.isSearchTargetPresent(target)){
			searchList.push_back(tempTask);
			}
		}
	}

void Planner::setCurrentDate(taskDate currentDate) {
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	currentDate.year = (now->tm_year - 100);
	currentDate.month = (now->tm_mon + 1);
	currentDate.day = (now->tm_mday);
	}

/*
void Planner::deleteTask(int index){
//find the index
list<taskWithID> ::iterator it = next7DaysList.begin();
for (int i = 0; i < index; i++){
it++;
}
//update the undoData, lastEntry Data Structure
lastEntry.lastCommand == "delete";
lastEntry.lastTask = *it;
//erase the entry at the index
next7DaysList.erase(it);
//generate next7daysList, upcomingList, missedList,
generate_next7DaysList();
generate_upcomingList();
generate_missedList();
}
int Planner::getIndexTodelete(int number, string nameOfList){
//find the ID number in the list
int idNumber;
if (number != 0){
idNumber = findIDNumber(number, nameOfList);
}
else {
idNumber = lastEntry.lastTask.idNumber;
}
//return the index
list<taskWithID> ::iterator it1;
list<taskWithID> ::iterator it2 = next7DaysList.begin();
int index = 0;
for (it1 = next7DaysList.begin(); it1 != next7DaysList.end(); it1++){
if (*it2.IDnumber == number){
return index;
}
else {
it2++;
index++;
}
}
//if  number is 0 means it is an undo. delete the last ID generated
//delete that
}
void Planner::editTask(int number, Task content){
//delete
//add
//update the undoData, lastEntry Data Structure
}
void Planner::undo(void){
//refer to the undoData
if (lastEntry.lastCommand == "add"){
deleteTask(0);
}
else if (lastEntry.lastCommand == "delete"){
addTask(lastEntry.lastTask);
}
else if (lastEntry.lastCommand == "edit"){
deleteTask(0);
addTask(lastEntry.lastTask);
}
else {
cout << "There is nothing to undo." << endl;
}
//do that command with that info
//generate next7daysList, upcomingList, missedList,
generate_next7DaysList();
generate_upcomingList();
generate_missedList();
}
void Planner::clear(void){
//clear the list
allTaskList.clear();
//generate next7daysList, upcomingList, missedList,
generate_next7DaysList();
generate_upcomingList();
generate_missedList();
}
bool Planner::checkForClash(taskDate, taskDate, taskTime, taskTime){
//go to main list
//check for overlaps
//if overlap return true
}
//Functions that generate the next7daysList,
//upcomingList, missedList, searchList
void Planner::generate_next7DaysList(void){
//get today's date
//run down the list, getting each date
//add the events that are in the range
}
void Planner::generate_upcomingList(void){
//get today's date
//find the earliest entry after today
//add in everything till the end of the list, including that entry
}
void Planner::generate_missedList(void){
//get today's date
//find all the dates before today's date
//add in everything till todays date
//when reach today's date, chech the time for today's date events only
//add in those missed by time also
//if no time specified then not considered missed until the next day
}
void Planner::generate_searchList(string target){
//go to start of list
//call the search function inside every entry
//everytime the return is true,add in that entry
}
//other functions
Tdate Planner::getTodaysDate(void){
//use c++ to get current date
time_t t = time(0);
//convert t to Tdate
return convertDate(t);
//return
}
Ttime Planner::getCurrentTime(void){
//use c++ to get current time
time_t t = time(0);
//convert to Ttime
return convertTime(t);
//return
}
int Planner::findIndexToSlotIn(taskDate startDate, taskDate endDate, taskTime startTime, taskTime endTime){
//run down the list
list<taskWithID> ::iterator it = allTaskList.begin();
int index = 0;
//while (it != allTaskList.end()){
//}
return index
//return the index to enter the item
}
int Planner::findIDNumber(int number, string nameofList){
list<taskWithID>::iterator it;
Task tempTask;
//return the ID number associated with the entry
if (nameofList == "allTaskList"){
it = allTaskList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "next7DaysList"){
it = next7DaysList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "upcomingList"){
it = upcomingList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "missedList"){
it = missedList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "searchList"){
it = searchList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
}
string Planner::toString(string nameOfList){
//convert the list to a string and return
string finalString;
if (nameOfList == "allTaskList"){
finalString = allTaskListToString();
return finalString;
}
else if (nameOfList == "next7DaysList"){
finalString = next7DaysListToString();
return finalString;
}
else if (nameOfList == "upcomingList"){
finalString = upcomingListToString();
return finalString;
}
else if (nameOfList == "missedList"){
finalString = missedListToString();
return finalString;
}
else if (nameOfList == "searchList"){
finalString = searchListToString();
return finalString;
}
}
string Planner::allTaskListToString(void){
}
string Planner::searchListToString(void){
}*/