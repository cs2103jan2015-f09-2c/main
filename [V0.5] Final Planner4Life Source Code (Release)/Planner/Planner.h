#ifndef PLANNER_H
#define PLANNER_H
#include "Task.h"
#include "Log.h"
#include <string>
#include <list>
using namespace std;

//Structures for dta storage for undo function
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

	//add helper function
	void placeToSlotAddedTask(list<Task>::iterator& listIter, Task newTask);

	// delete helper functions
	int getNewId(void);
	string deleteIndex(int idNumber);
	void indexChecker(list<Task>::iterator&, int, list<Task>&);

	//undo helper functons
	void updateLastEntryStructure(string, Task);

	// mark done helper function
	string markDoneIndex(int idNumber);

	//check duplicate helper function
	bool isDuplicatePresent(Task newTask);
	bool tasksAreTheSame(Task Task1, Task Task2);

	//Clash Helper Functions
	void clearClashList();
	void checkListForClashes();
	bool isDatesClash(Task, Task);
	bool isTwoDateTasksOverlapping(Task, Task);
	bool task2EndDateOverlapTask1StartDate(taskDate, taskDate, taskDate, taskDate);
	bool task1EndDateOverlapTask2StartDate(taskDate, taskDate, taskDate, taskDate);
	bool isTask1StartBeforeOrSameAsTask2Start(taskDate, taskDate);
	bool isTimesClash(Task, Task);
	bool isTask1EndAfterTask2Start(taskDate, taskDate);
	bool checkTaskForClashes(Task Task1, Task Task2);
	bool isTwoDatesTasksSameDates(Task, Task);
	bool isOneDateTasksSameDates(Task, Task);
	bool isOneDateTaskbetweenTwoDateTask(Task, Task);

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
	string ListToString(list<Task>);

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

	//check if missed list is empty
	bool isMissedEmpty();
};
#endif // !PLANNER_H

