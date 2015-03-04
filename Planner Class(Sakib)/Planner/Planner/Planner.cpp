#include "Planner.h"
#include<iostream>
#include<string>
#include<list>
#include <ctime>

using namespace std;

//Functions that edit the allTaskList ONLY
void Planner::addTask(task content){
	//create new task
	Task newTask;
	//add in the details
	newTask = content; // i dont know if this correct
	//check time and date
	taskTime StartTime = newTask._timeStart;
	taskTime EndTime = newTask._timeEnd;
	taskDate StartDate = newTask._dateStart;
	taskDate EndDate = newTask._dateEnd;
	//check for clash
	bool clash;
	clash=checkForClash(StartTime, EndTime, StartDate, EndDate);
	//if no clash,
	//find spot to enter
	int index;
	if (!clash){
		index = findIndexToSlotIn(StartTime, EndTime, StartDate, EndDate);
	}
	
	//enter in to the list
	list<Task>::iterator it = allTaskList.begin();
	for (int i = 0; i < index; i++){
		it++;
	}
	allTaskList.insert(it,newTask);
	//generate next7daysList, upcomingList, missedList,
	generate_next7DaysList();
	generate_upcomingList();
	generate_missedList();
	//update the undoData, lastEntry Data Structure
}

void Planner::deleteTask(int number){
	//find the ID number in the list
	//if id number is 0 means it is an undo. delete the last ID generated
	//delete that
	//generate next7daysList, upcomingList, missedList,
	generate_next7DaysList();
	generate_upcomingList();
	generate_missedList();
	//update the undoData, lastEntry Data Structure
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
		cout<< "There is nothing to undo." << endl;
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

bool Planner::checkForClash(Tdate, Tdate,Ttime,Ttime){
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

int Planner::findIndexToSlotIn(Tdate, Tdate, Ttime, Ttime){
	//run down the list
	//return the index to enter the item
}

int Planner::fndIDNumber(int number){
	//return the ID number associated with the entry
}

string Planner::toString(list<task> List){
	//convert the list to a string and return
}