#ifndef PLANNER_H
#define PLANNER_H
#include "Task.h"
#include "Log.h"
#include <string>
#include <list>
using namespace std;

struct undoData{
	string lastCommand = "";
	Task lastTask;
};

struct undoEditData{
	Task deletedTask;
	Task addedTask;
};

class Planner{

private:

	// All the private lists present in Planner
	list<Task> All; // Master List of all the Tasks
	list<Task> homeList;
	list<Task> upcomingList;
	list<Task> missedList;
	list<Task> searchList;
	list<Task> doneList;
	
	// List of all the Log Data
	Log* LogData = Log::getInstance();
	
	//Undo Structures
	undoData lastEntry;
	undoEditData lastEdit;
	
	//Time Structure
	taskDate currentDate;
	
	//status returning functions
	string descriptionOfTaskToString(Task theTask);
	string addStatusToString(Task theTask);
	string deleteStatusToString(Task theTask);
	string editStatusToString();
	string undoStatusToString();
	string clearStatusToString();
	string saveStatusToString();
	string searchStatusToString();
	string doneStatusToString();
	string duplicateStatusToString(Task theTask);
	// List returning functions
	string homeListToString(void);
	string upcomingListToString();
	string missedListToString();
	string searchListToString();
	string doneListToString();
	// delete helper functions
	int getIdOfLastEntry(void);
	string deleteIndex(int idNumber);
	//save helper function
	
	//list generating functions
	void generateAllOtherList(void);
	void generateHomeList(void);
	void generateUpcomingList(void);
	void generateMissedList(void);
	void generateDoneList(void);
	// list boolean functions
	bool isHome(taskDate, list<Task>::iterator);
	bool isMissed(taskDate, list<Task>::iterator);
	bool isUpcoming(taskDate, list<Task>::iterator);
	// mark done function
	string markDoneIndex(int idNumber);
	//check duplicate function
	bool isDuplicatePresent(Task newTask);
	bool tasksAreTheSame(Task Task1, Task Task2);
	//check clashes
	bool isClashPresent(Task newTask);
	void checkListForClashes();
	bool checkTaskForClashes(Task Task1, Task Task2);
	bool isClashTaskSingleDateTimeTaskDoubleDateTime(Task, Task);
	bool isTwoDatesTasksSameDates(Task, Task);
	bool isOneDateTasksSameDates(Task, Task);
	bool isOneDateTaskbetweenTwoDateTask(Task, Task);
	bool taskTimesOverlap(Task, Task);
	bool isOneTimeTaskBetweenTwoTimesTask(Task, Task);

	bool indexChecker(list<Task>::iterator&, int, list<Task>&);
	
public:
	// Initialization 
	Planner();
	//command functions to be called by Logic
	string addTask(Task content);
	string deleteTask(int serialNumber, string nameOfList);
	string undo(void);
	string clear(void);
	string editTask(int serialNumber, string nameOfList, string input);
	string markDone(int serialNumber, string nameOfList);
	//string save(string);
	string generateSearchList(string target);
	// string of list returning function
	string toString(string nameOfList);
	string AllToString(void);
	//string of status returning function
	string statusToString(string command, Task theTask);
	string saveDataToString();
	//load from save file
	void loadData(string data);
};
#endif // !PLANNER_H

