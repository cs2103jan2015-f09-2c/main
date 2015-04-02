#ifndef TASK_H
#define TASK_H
#include "Log.h"
#include <iostream>
#include <string>
#include <list>


using namespace std;

struct taskDate{
	int day = -1;
	int month = -1;
	int year = -1;					//2 digits only
};

class Task{
private:
	string _description;
	int _timeStart = -1;
	int _timeEnd = -1;
	taskDate _dateStart;
	taskDate _dateEnd;
	bool _isImpt;
	bool _isDone;
	bool _isClash;
	int _idNumber;
	int _numOfDates;
	int _numOfTimes;
	list<Task> _recurringTasks;
	string processImportance(string);
	string processDescription(string);			
	void processDate(string);					
	void processTime(string);					
	void storeStartDate(string);				
	void storeEndDate(string);
	string modifyDetails(int, string, string);
	string extractDateInfo(string);
	void modifyStartandEndDate(string, string, string);		//check if need
	string modifyDate(string, string);
	string insertNewDateInfo(string, string);
	string processDailyRecur(string);
	string processWeeklyRecur(string);
	string processMonthlyRecur(string);
	string processYearlyRecur(string);
	void splitDate(string, int&, int&, int&);
	void mergeDate(string&, int, int, int);
	int extractDateInfoFields(string, string&, string&, string&, string&);
	Log* LogData = Log::getInstance();

public:
	Task();
	~Task();
	
	void addDetails(string);
	void recurTask(string);
	bool isSearchTargetPresent(string);
	string getDescription();
	int getTimeStart();
	int getTimeEnd();
	taskDate getDateStart();
	taskDate getDateEnd();
	bool getImportance();
	bool doneStatus();
	int getIdNumber();
	int getNumOfDates();
	int getNumOfTimes();
	void storeIdNumber(int);
	void markIsDoneAsTrue();
	list<Task> getRecurringTasks();
	bool areDatesTheSame(taskDate,taskDate);
	void markClashAsTrue();
	bool clashStatus();
};
#endif


