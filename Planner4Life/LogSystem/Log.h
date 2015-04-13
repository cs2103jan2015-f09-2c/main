#pragma once
#include<string>
#include<vector>
using namespace std;
class Log
{
private:
	Log();
	~Log();

	static bool _instanceFlag;
	static Log *theOne;
	vector<string> _logList;
	int _numLines;
	int MAX_LINES = 1000;

	void saveLog(string);
	int numOfLinesInFile();

public:
	static Log* getInstance();
	void addLog(string type, string message);
	void clearLogFile();
};

