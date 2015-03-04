#ifndef PLANNER_H
#define PLANNER_H
include "Task.h"

#include <string>
#include <list>
using namespace std;

class Planner{

private:
	list<Task> allTaskList;
	list<Task> next7DaysList;
	list<Task> upcomingList;
	list<Task> missedList;
	list<Task> searchList;
	
	//a data structure to store the last command and information
	//maybe an array

public:
	//Functions that edit the allTaskList ONLY
	void addTask(task content);
	void deleteTask(int number);
	void undo(void);
	void clear(void);
	bool checkForClash(Tdate, Tdate, Ttime, Ttime);

	//Functions that generate the next7daysList,
	//upcomingList, missedList, searchList
	void generate_next7DaysList(void);
	void generate_upcomingList(void);
	void generate_missedList(void);
	void generate_searchList(string target);

	//other functions
	Tdate getTodaysDate(void);
	Ttime getCurrentTime(void);
	Tdate convertDate(time_t t);
	Ttime convertTime(time_t t);
	int findIndexToSlotIn(Tdate, Tdate, Ttime, Ttime);
	int fndIDNumber(int number);
	string toString(list<task>)

};
#endif // !PLANNER_H
