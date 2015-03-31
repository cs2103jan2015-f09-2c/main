#ifndef PLANNER_H
#define PLANNER_H
#include "Task.h"
#include "Log.h"
#include <string>
#include <list>
using namespace std;

struct undoData{
	string lastCommand;
	Task lastTask;
};

struct undoEditData{
	Task deletedTask;
	Task addedTask;
};

class Planner{

private:
	// all the private lists
	list<Task> All; // allTaskList 
	list<Task> HomeList;
	list<Task> UpcomingList;
	list<Task> MissedList;
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
	// List reurning functions
	string HomeListToString(void);
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

	string markDoneIndex(int idNumber);
public:

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

