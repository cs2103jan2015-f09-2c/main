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
	list<Task> All; // allTaskList 
	list<Task> HomeList;
	list<Task> UpcomingList;
	list<Task> MissedList;
	list<Task> searchList;

	undoData lastEntry;
	undoEditData lastEdit;

	taskDate currentDate;

	string addStatusToString(Task theTask);
	string deleteStatusToString(Task theTask);
	string editStatusToString();
	string undoStatusToString();
	string clearStatusToString();
	string saveStatusToString();
	string saveDataToString();

	string AllToString(void);
	string HomeListToString(void);
	string upcomingListToString();
	string missedListToString();
	string searchListToString();

	int getIdOfLastEntry(void);
	string deleteIndex(int idNumber);

	void generateAllOtherList(void);
	void generateHomeList(void);
	void generateUpcomingList(void);
	void generateMissedList(void);
	void generateSearchList(string target);

	bool isHome(taskDate, list<Task>::iterator);
	bool isMissed(taskDate, list<Task>::iterator);
	bool isUpcoming(taskDate, list<Task>::iterator);

public:

	Planner();
	string addTask(Task content);
	string deleteTask(int serialNumber, string nameOfList);
	string toString(string nameOfList);
	string statusToString(string command, Task theTask);
	string undo(void);
	string clear(void);
	string editTask(int serialNumber, string nameOfList, string input);
	string save(string);




};
#endif // !PLANNER_H

