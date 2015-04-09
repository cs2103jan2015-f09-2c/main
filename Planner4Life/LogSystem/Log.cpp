#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<ctime>
#include<vector>
#include "Log.h"

bool Log::instanceFlag = false;
Log* Log::theOne = NULL;

//@author A0111361Y
Log* Log::getInstance(){
	if (!instanceFlag)
	{
		theOne = new Log();
		instanceFlag = true;
		return theOne;
	}
	else
	{
		return theOne;
	}
}

//@author A0111361Y
Log::Log(void){
	_numLines = 0;
}

//@author A0111361Y
Log::~Log(){
}

//@author A0111361Y
void Log::addLog(string type, string message){

	ostringstream out;
	time_t _tm = time(NULL);
	struct tm * curtime = localtime(&_tm);
	out << type << ": " << message << "; " << asctime(curtime);
	string text = out.str();
	_numLines = _numLines + 1;
	_logList.push_back(text);
	saveLog();

}

//KARTHIK
void Log::saveLog(void){
	ofstream outFile;

	if (numOfLinesInFile() > _maxLines){
		clearLogFile();
		_numLines++;
	}


	outFile.open("Planner4Life_Log_File.txt", std::ios::app);
	/*
	*/
	outFile << /*_numLines << "." <<*/ _logList[_numLines - 1] << endl;

	outFile.close();
}

//KARTHIK
int Log::numOfLinesInFile(){
	int numOfLines = 0;
	string line;
	ifstream readFile("Planner4Life_log_File.txt");

	while (getline(readFile, line)){
		numOfLines++;
	}

	return numOfLines;
}

//@author A0111361Y
void Log::clearLogFile(){
	ofstream outFile("Planner4Life_Log_File.txt");
	outFile << "";
	outFile.close();
	_numLines = 0;
}

