#pragma once
#include<string>
#include<vector>
using namespace std;
class Log
{
private: 
	vector<string> _logList;
	int _numLines;
	void saveLog();
	void loadLog();

public:
	Log();
	~Log();
	void addLog(string type, string message);
	void clearLog();
};

