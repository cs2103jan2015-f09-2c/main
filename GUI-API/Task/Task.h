#ifndef TASK_H
#define TASK_H
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
	//	taskTime _timeStart;
	//	taskTime _timeEnd;
	int _timeStart = -1;
	int _timeEnd = -1;
	taskDate _dateStart;
	taskDate _dateEnd;
	bool _isImpt;
	int _idNumber;

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
	bool isImpt();
	void processDate(string);
	void processTime(string);
	void storeStartDate(string);
	void storeEndDate(string);
	void storeIdNumber(int);
	int getIdNumber();
};
#endif

