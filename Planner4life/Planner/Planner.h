#ifndef PLANNER_H
#define PLANNER_H
#include "C:\Users\User\Desktop\CS2103 Project\Planner4life\Task\Task.h"
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
	list<Task> next7DaysList;
	list<Task> UpcomingList;
	list<Task> MissedList;
	list<Task> searchList;

	undoData lastEntry;
	undoEditData lastEdit;

	taskDate currentDate;

public:

	Planner();
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
	string AllToString(void);
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

	void generateAllOtherList(void);
	void generateNext7DaysList(void);
	void generateUpcomingList(void);
	void generateMissedList(void);

	void generateSearchList(string target);
	bool isNext7Days(taskDate, list<Task>::iterator);
	bool isMissed(taskDate, list<Task>::iterator);
	bool isUpcoming(taskDate, list<Task>::iterator);
};
#endif // !PLANNER_H
