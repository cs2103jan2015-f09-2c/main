#ifndef TASK_H
#define TASK_H
#include "Log.h"
#include <iostream>
#include <string>


using namespace std;

struct taskDate{
	int day = -1;
	int month = -1;
	int year = -1;					//2 digits only
};

class Task{
private:
	string _description;
	int _timeStart;
	int _timeEnd;
	taskDate _dateStart;
	taskDate _dateEnd;
	bool _isImpt;
	int _idNumber;
	int _numOfDates;
	int _numOfTimes;
	string processImportance(string);
	string processDescription(string);
	void processDate(string);
	void processTime(string);
	void storeStartDate(string);
	void storeEndDate(string);
	Log LogData;
public:
	Task();
	~Task();
	void addDetails(string);
	bool isSearchTargetPresent(string);
	string getDescription();
	int getTimeStart();
	int getTimeEnd();
	taskDate getDateStart();
	taskDate getDateEnd();
	bool getImportance();
	int getIdNumber();
	int getNumOfDates();
	int getNumOfTimes();
	void storeIdNumber(int);
};
#endif


