#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <string>

using namespace std;

struct taskTime{
	int hour;
	int min;
	string timeOfDay;			//remove this, stick to 24hr format
	};

struct taskDate{
	int day;
	int month;
	int year;					//2 digits only
	};

class Task{
private:
	string _description;
	taskTime _timeStart;
	taskTime _timeEnd;
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
	taskTime getTimeStart();
	taskTime getTimeEnd();
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
