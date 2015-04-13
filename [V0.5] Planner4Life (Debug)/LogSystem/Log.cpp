#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<ctime>
#include<vector>
#include "Log.h"

const string DEFAULT_LOGFILE_LOCATION = "Planner4Life_Log_File.txt";

bool Log::_instanceFlag = false;
Log* Log::theOne = NULL;

//@author A0111361Y
Log* Log::getInstance(){
	if (!_instanceFlag)
	{
		theOne = new Log();
		_instanceFlag = true;
	}

	return theOne;
}

Log::Log(void){
	_numLines = 0;
}

Log::~Log(){
}

void Log::addLog(string type, string message){
	ostringstream out;
	time_t _tm = time(NULL);
	struct tm * curtime = localtime(&_tm);

	out << type << ": " << message << "; " << asctime(curtime);
	string text = out.str();

	saveLog(text);

}

void Log::clearLogFile(){
	ofstream outFile(DEFAULT_LOGFILE_LOCATION);

	outFile << "";
	outFile.close();
	_numLines = 0;
}

//@author A0111061E
void Log::saveLog(string text){
	ofstream outFile;

	if (numOfLinesInFile() > MAX_LINES){
		clearLogFile();
	}

	_numLines = numOfLinesInFile();
	_numLines++;

	outFile.open(DEFAULT_LOGFILE_LOCATION, std::ios::app);
	outFile << _numLines << ". " << text;

	outFile.close();
}

int Log::numOfLinesInFile(){
	int numOfLines = 0;
	string line;
	ifstream readFile(DEFAULT_LOGFILE_LOCATION);

	while (getline(readFile, line)){
		numOfLines++;
	}

	return numOfLines;
}