#include "Planner.h"
#include<string>
#include<list>
#include <ctime>

using namespace std;

//Functions that edit the allTaskList ONLY
void Planner::addTask(task content){
	//create new event
	//add in the details
	//check time and date
	//find spot to enter
	//check for clash
	//if no clash,
	//enter in to the list
	//generate next7daysList, upcomingList, missedList,
	generate_next7DaysList();
	generate_upcomingList();
	generate_missedList();
}

void Planner::deleteTask(int number){
	//find the ID number in the list
	//delete that
	//generate next7daysList, upcomingList, missedList,
	generate_next7DaysList();
	generate_upcomingList();
	generate_missedList();
}

void Planner::undo(void){
	//refer to the data structure containing command and info
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