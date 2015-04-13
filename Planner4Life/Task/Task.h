#ifndef TASK_H
#define TASK_H
#include "Log.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

struct taskDate{		// date fields are in 2-digit format i.e. 010415
	int day = -1;
	int month = -1;
	int year = -1;	
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
	Log* LogData = Log::getInstance();
	list<Task> _recurringTasks;

	//Helper functions for AddDetails
	void processImportance(string&);
	void processDescription(string&);
	void processDate(string);
	void processTwoDates(string, string);
	void processOneDate(string);
	void storeStartDate(string);
	void storeEndDate(string);
	void processTime(string);
	void storeStartTime(string);
	void storeEndTime(string);
	void process_NoDelimiter(string);
	void process_OneDelimiter(string);
	void process_TwoDelimiter(string);

	//Helper functions for Recur
	void processRecur(string, string, int);
	string modifyDetails(string, string);
	string extractDateInfo(string);
	string modifyDate(string, string);
	string insertNewDateInfo(string, string);
	string processDailyRecur(string);
	bool is31DayMonth(int);
	string processWeeklyRecur(string);
	string processMonthlyRecur(string);
	string processYearlyRecur(string);
	void splitDate(string, int&, int&, int&);
	void mergeDate(string&, int, int, int);
	int extractDateInfoFields(string, string&, string&, string&, string&);
	string extractTaskDetailsFromUserInput(string);

	//Checker functions for general exception handling
	bool areValidDates(string, string);
	bool isValidDate(string);
	bool startDateBeforeEndDate(string, string);
	bool correctDateLength(string);
	bool areValidTimes(string, string);
	bool isValidTime(int);
	bool startTimeBeforeEndTime(int, int);

public:
	Task();
	~Task();	

	//Functions to add Task details
	void addDetails(string);
	void recurTask(string);

	//Getter functions for Task variables
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
	list<Task> getRecurringTasks();
	bool areDatesTheSame(taskDate, taskDate);
	bool isSearchTargetPresent(string);

	//Public operations on Task variables
	void storeIdNumber(int);
	void markIsDoneAsTrue();
	bool clashStatus();
	void markClashAsTrue();
	void markClashAsFalse();
};
#endif


