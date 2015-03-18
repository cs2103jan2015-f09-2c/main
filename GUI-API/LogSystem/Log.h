#pragma once
#include<string>
#include<vector>
using namespace std;
class Log
{
private: 
	vector<string> _logList;
	vector<int> _numberList;

public:
	Log();
	~Log();
	int _numLines;
	void addLog(string type, string message);
	void saveLog();
};

