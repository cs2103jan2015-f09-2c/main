#ifndef PLANNER_H
#define PLANNER_H
include "Task.h";

#include <string>
#include <list>
using namespace std;

struct undoData{
	string lastCommand; // should be add/delete/edit
	Task lastTask;
	};

struct taskWithID{
	Task aTask;
	int IDnumber;
	};
class Planner{

private:
	list<taskWithID> allTaskList;
	list<taskWithID> next7DaysList;
	list<taskWithID> upcomingList;
	list<taskWithID> missedList;
	list<taskWithID> searchList;
	
	undoData lastEntry;

public:
	//Functions that edit the allTaskList ONLY
	void addTask(Task content);
	void deleteTask(int index);
	int getIndexTodelete(int number, string nameOfList);
	void editTask(int number, Task content);
	void undo(void);
	void clear(void);
	bool checkForClash(taskDate,taskDate,taskTime,taskTime);

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
	int findIDNumber(int number, string nameOfList);
	//toSting functions
	string toString(string nameOfList);
	string allTaskListToString(void);
	string next7DaysListToString(void);
	string upcomingListToString(void);
	string missedListToString(void);
	string searchListToString(void);

};
#endif // !PLANNER_H
