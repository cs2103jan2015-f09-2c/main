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
	
	// delete helper functions
	int getIdOfLastEntry(void);
	string deleteIndex(int idNumber);
	//undo helper functons
	void updateLastEntryStructure(string, Task);
	// mark done helper function
	string markDoneIndex(int idNumber);
	//check duplicate helper function
	bool isDuplicatePresent(Task newTask);
	bool tasksAreTheSame(Task Task1, Task Task2);
	//Clash Helper Functions
	//bool isClashPresent(Task newTask);
	void checkListForClashes();
	bool checkTaskForClashes(Task Task1, Task Task2);
	bool isClashTaskSingleDateTimeTaskDoubleDateTime(Task, Task);
	bool isTwoDatesTasksSameDates(Task, Task);
	bool isOneDateTasksSameDates(Task, Task);
	bool isOneDateTaskbetweenTwoDateTask(Task, Task);
	bool taskTimesOverlap(Task, Task);
	bool isOneTimeTaskBetweenTwoTimesTask(Task, Task);
	bool indexChecker(list<Task>::iterator&, int, list<Task>&);
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
	//list generating functions
	void generateAllOtherList(void);
	void generateHomeList(void);
	void generateUpcomingList(void);
	void generateMissedList(void);
	void generateDoneList(void);
	void clearTheLists(void);
	void generateTheLists(void);
	// Generator Logic Functions
	bool isHome(taskDate, list<Task>::iterator);
	bool checkHomeDate(taskDate, int, int, int);
	bool isMissed(taskDate, list<Task>::iterator);
	bool checkMissedDate(taskDate, int, int, int);
	bool isUpcoming(taskDate, list<Task>::iterator);
	// List returning functions
	string homeListToString(void);
	string upcomingListToString();
	string missedListToString();
	string searchListToString();
	string doneListToString();
	
	

	
	
public:
	// Initialization 
	Planner();
	//Command Functions
	string addTask(Task content);
	string deleteTask(int serialNumber, string nameOfList);
	string undo(void);
	string clear(void);
	string editTask(int serialNumber, string nameOfList, string input);
	string markDone(int serialNumber, string nameOfList);
	string generateSearchList(string target);
	// Functions that returns Lists in string form
	string toString(string nameOfList);
	string AllToString(void);
	//string of status returning function
	string statusToString(string command, Task theTask);
	string saveDataToString();
	//load from save file
	void loadData(string data);
};
#endif // !PLANNER_H

