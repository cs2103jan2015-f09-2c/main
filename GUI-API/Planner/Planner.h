#ifndef PLANNER_H
#define PLANNER_H
#include "Task.h"

#include <string>
#include <list>
using namespace std;



struct undoData{
	string lastCommand; // should be add/delete/edit
	Task lastTask;
};


class Planner{

private:
	list<Task> allTaskList;
	list<Task> next7DaysList;
	list<Task> upcomingList;
	list<Task> missedList;
	list<Task> searchList;

	undoData lastEntry;

public:

	void addTask(Task content);
	string toString(string);
	string allTaskListToString(void);
	int getIdOfLastEntry(void);
	void deleteTask(int serialNumber, string nameOfList);
	void deleteIndex(int idNumber);
	void undo(void);
	void clear(void);
	void editTask(int serialNumber, string nameOfList, string input);


	//void editTask(int number, Task content);
	//bool checkForClash(taskDate, taskDate, taskTime, taskTime);
	/*
	//Functions that generate the next7daysList,
	//upcomingList, missedList, searchList
	void generate_next7DaysList(void);
	void generate_upcomingList(void);
	void generate_missedList(void);
	void generate_searchList(string target);*/
	/*
	//other functions
	Tdate getTodaysDate(void);
	Ttime getCurrentTime(void);
	Tdate convertDate(time_t t);
	Ttime convertTime(time_t t);
	int findIndexToSlotIn(Tdate, Tdate, Ttime, Ttime);
	int findIDNumber(int number, string nameOfList);
	//toSting functions
	string next7DaysListToString(void);
	string upcomingListToString(void);
	string missedListToString(void);
	string searchListToString(void);
	*/
};
#endif // !PLANNER_H