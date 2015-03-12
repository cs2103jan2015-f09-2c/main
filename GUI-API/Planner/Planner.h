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

struct undoEditData{
	Task deletedTask;
	Task addedTask;
};

class Planner{

private:
	list<Task> Home; // allTaskList
	list<Task> next7DaysList;
	list<Task> UpcomingList;
	list<Task> MissedList;
	list<Task> searchList;

	undoData lastEntry;
	undoEditData lastEdit;

	taskDate currentDate;

public:

	string addTask(Task content);
	string toString(string nameOfList);
	string statusToString(string command, Task theTask);
	string addStatusToString(Task theTask);
	string deleteStatusToString(Task theTask);
	string editStatusToString();
	string undoStatusToString();
	string clearStatusToString();
	string saveStatusToString();
	string saveDataToString();
	string HomeToString(void);
	string next7DaystoString(void);
	string upcomingListToString();
	string missedListToString();
	string searchListToString();
	int getIdOfLastEntry(void);
	string deleteTask(int serialNumber, string nameOfList);
	string deleteIndex(int idNumber);
	string undo(void);
	string clear(void);
	string editTask(int serialNumber, string nameOfList, string input);
	string save(string);
	void setCurrentDate(taskDate&);

	void generateAllOtherList(void);
	void generateNext7DaysList(void);
	void generateUpcomingList(void);
	void generateMissedList(void);

	void generateSearchList(string target);
	int isHomeView(taskDate, list<Task>::iterator);

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
