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
	void saveLog();
//	int numOfLinesInFile();
	//void loadLog();


public:
	static Log* getInstance();
	void addLog(string type, string message);
	void clearLog();
};

