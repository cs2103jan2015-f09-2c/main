#pragma once
#include<string>
#include<vector>
using namespace std;
class Log
{
private:
	Log();
	~Log();
	static bool instanceFlag;
	static Log *theOne;
	vector<string> _logList;
	int _numLines;
	int _maxLines = 1000;
	void saveLog(string);
	int numOfLinesInFile();
	//void loadLog();


public:
	static Log* getInstance();
	void addLog(string type, string message);
	void clearLogFile();
};

