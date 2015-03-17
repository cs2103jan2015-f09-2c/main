#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<ctime>
#include "Log.h"


Log::Log(void){
	_numLines = 0;
}


Log::~Log(){
}

void Log::addLog(string type, string message){
	ostringstream out;
	time_t _tm = time(NULL);
	struct tm * curtime = localtime(&_tm);
	out << type << ": " << message << "; "<<asctime(curtime);
	string text = out.str();
	_numLines++;
	_numberList.push_back(_numLines);
	_logList.push_back(text);
	saveLog();
	
	}

void Log::saveLog(void){
	ofstream outFile("Planner4Life_Log_File.txt");
	for (int i = 0; i < _numLines; i++){
		outFile << _numberList[i] << "." << _logList[i] << endl;
	}
	outFile.close();
}
