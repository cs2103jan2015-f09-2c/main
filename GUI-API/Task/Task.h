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
	Log* LogData = Log::getInstance();
	list<Task> _recurringTasks;

	void processImportance(string&);
	void processDescription(string&);			
	void processDate(string);					
	void storeStartDate(string);				
	void storeEndDate(string);
	void processTime(string);
	void storeStartTime(string);
	void storeEndTime(string);
	void process_NoDelimiter(string);
	void process_OneDelimiter(string);
	void process_TwoDelimiter(string);

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


