#include "Planner.h"
#include<iostream>
#include<string>
#include<list>
#include <ctime>

using namespace std;

//Functions that edit the allTaskList ONLY
void Planner::addTask(Task content){
	//create new task
	taskWithID newTaskWithID;
	Task newTask;
	newTaskWithID.IDnumber = 0001;
	//add in the details
	newTask = content; // i dont know if this correct
	//check time and date
	//taskTime StartTime = newTask._timeStart;
	//taskTime EndTime = newTask._timeEnd;
	//taskDate StartDate = newTask._dateStart;
	//taskDate EndDate = newTask._dateEnd;
	//check for clash
	bool clash = false;
	//clash=checkForClash(StartTime, EndTime, StartDate, EndDate);
	//if no clash,
	//find spot to enter
	int index;
	//taskTime startTime, endTime;
	//taskDate startDate, endDate;
	//startTime = content.aTask.getTimeStart();
	//endTime = content.aTask.getTimeEnd();
	//startDate = content.aTask.getDateStart();
	//endDate = content.aTask.getDateEnd();
	//if (!clash){
		//index = findIndexToSlotIn(startDate, endDate, startTime, endTime);
		//}

	//enter in to the list
	list<taskWithID>::iterator it = allTaskList.begin();
	for (int i = 0; i < index; i++){
		it++;
		}
	allTaskList.insert(it, newTaskWithID);
	//generate next7daysList, upcomingList, missedList,
	generate_next7DaysList();
	generate_upcomingList();
	generate_missedList();
	//update the undoData, lastEntry Data Structure
	}
void Planner::deleteTask(int index){
	//find the index
	list<taskWithID> ::iterator it = next7DaysList.begin();
	for (int i = 0; i < index; i++){
		it++;
		}
	//update the undoData, lastEntry Data Structure
	lastEntry.lastCommand == "delete";
	lastEntry.lastTask.aTask = (*it).aTask;
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
		idNumber = lastEntry.lastTask.IDnumber;
		}
	//return the index
	list<taskWithID> ::iterator it1;
	list<taskWithID> ::iterator it2 = next7DaysList.begin();
	int index = 0;
	for (it1 = next7DaysList.begin(); it1 != next7DaysList.end(); it1++){
		if ((*it2).IDnumber == number){
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
/*
void Planner::editTask(int number, taskWithID content){
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
		addTask(lastEntry.lastTask.aTask);
		}
	else if (lastEntry.lastCommand == "edit"){
		deleteTask(0);
		addTask(lastEntry.lastTask.aTask);
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
	return true;
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
taskDate Planner::getTodaysDate(void){
	//use c++ to get current date
	time_t t = time(0);
	//convert t to Tdate
	return convertDate(t);
	//return
	}

taskTime Planner::getCurrentTime(void){
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
	return index;
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
		return (*it).IDnumber;

		}
	else if (nameofList == "next7DaysList"){
		it = next7DaysList.begin();
		for (int i = 0; i < number; i++){
			it++;
			}
		return (*it).IDnumber;
		}
	else if (nameofList == "upcomingList"){
		it = upcomingList.begin();
		for (int i = 0; i < number; i++){
			it++;
			}
		return (*it).IDnumber;
		}
	else if (nameofList == "missedList"){
		it = missedList.begin();
		for (int i = 0; i < number; i++){
			it++;
			}
		return (*it).IDnumber;
		}
	else if (nameofList == "searchList"){
		it = searchList.begin();
		for (int i = 0; i < number; i++){
			it++;
			}
		return (*it).IDnumber;
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
	return "nill";
	}

string Planner::next7DaysListToString(void){
	return "nill";
	}

string Planner::upcomingListToString(void){
	return "nill";
	}

string Planner::missedListToString(void){
	return "nill";
	}

string Planner::searchListToString(void){
	return "nill";
	}*/