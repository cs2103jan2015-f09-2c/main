#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<ctime>
#include<vector>
#include "Log.h"


Log::Log(void){
	_numLines = 0;
}


Log::~Log(){
}

void Log::addLog(string type, string message){
	loadLog();
//
	ostringstream out;
	time_t _tm = time(NULL);
	struct tm * curtime = localtime(&_tm);
	out << type << ": " << message << "; "<<asctime(curtime);
	string text = out.str();
	_numLines = _numLines + 1;
	_logList.push_back(text);
	saveLog();
	
	}

void Log::saveLog(void){
	ofstream outFile("Planner4Life_Log_File.txt");
	
	for (int i = 1; i <= _numLines; i++){
		outFile << i << "." << _logList[i - 1] << endl;
	}
	outFile.close();
}

void Log::loadLog(void){
	ifstream readFile("Planner4Life_log_File.txt");
	string line;

	while (!_logList.empty()){
		_logList.pop_back();
	}

	while (getline(readFile, line)){
		_logList.push_back(line);
	}

	vector<string>::iterator iter;
	for (iter = _logList.begin(); iter != _logList.end(); ++iter){
		if (*iter == ""){
			iter = _logList.erase(iter);
			if (iter == _logList.end()){
				break;
			}
		}
	}
	
	vector<string>::iterator iter1;
	int i = 0;
	for (iter1 = _logList.begin(); iter1 != _logList.end(); ++iter1){
		i++;
		if (i <= 9){
			(*iter1).erase(0, 2);
		}
		else {
			(*iter1).erase(0, 3);
		}
	}

	_numLines = _logList.size();
}

void Log::clearLog(){
	while (!_logList.empty()){
		_logList.pop_back();
	}
	_numLines = _logList.size();
	saveLog();
}