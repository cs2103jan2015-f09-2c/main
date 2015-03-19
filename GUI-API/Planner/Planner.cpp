#include "Planner.h"
#include "Log.h"
#include <iostream>
#include <string>
#include <list>
#include <ctime>
#include <sstream>
#include <fstream>

using namespace std;

Planner::Planner(){
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	currentDate.year = (now->tm_year - 100);
	currentDate.month = (now->tm_mon + 1);
	currentDate.day = (now->tm_mday);
}

//Functions that edit the HomeONLY
string Planner::addTask(Task newTask){
	//create new task
	int id = getIdOfLastEntry(); // use static to actually create id
	
	//logging
	stringstream message;
	message << "ID of new entry is " << id;
	LogData.addLog("UPDATE", message.str());
	newTask.storeIdNumber(id);

	//check where to slot
	list<Task>::iterator iter;
	for (iter = All.begin(); iter != All.end(); ++iter){
		if (newTask.getDateStart().year <= (*iter).getDateStart().year)
			if (newTask.getDateStart().month < (*iter).getDateStart().month)
				break;
			else
				if (newTask.getDateStart().month == (*iter).getDateStart().month)
					if (newTask.getDateStart().day < (*iter).getDateStart().day)
						break;
					else
						if (newTask.getDateStart().day == (*iter).getDateStart().day){
							if (newTask.getTimeStart() <= (*iter).getTimeStart())
								break;
						}
	}

	/*
	for (iter = All.begin(); iter != All.end(); ++iter){
	if ((*iter).getTimeStart() > newTask.getTimeStart()){
	break;
	}
	if ((*iter).getTimeStart() == newTask.getTimeStart()){
	if ((*iter).getNumOfTimes() == 2 && newTask.getNumOfTimes() == 2){
	if (((*iter).getTimeEnd() - (*iter).getTimeStart()) > (newTask.getTimeEnd() - newTask.getTimeStart())){
	break;
	}
	}

	if (((*iter).getNumOfTimes() == 2 && newTask.getNumOfTimes() == 1)){
	break;
	}

	if (((*iter).getNumOfTimes() == 1 && newTask.getNumOfTimes() == 2)){
	iter++;
	break;
	}

	if (((*iter).getNumOfTimes() == 1 && newTask.getNumOfTimes() == 1)){
	if ((*iter).getIdNumber() > newTask.getIdNumber())
	break;
	}
	}
	}*/


	All.insert(iter, newTask);
	string status;
	status = statusToString("add", newTask);
	lastEntry.lastCommand = "add";
	lastEntry.lastTask = newTask;

	generateAllOtherList();

	return status;



}

string Planner::saveDataToString(){
	ostringstream out;
	list<Task> ::iterator it;
	it = All.begin();

	if (!All.empty()){
		for (it = All.begin(); it != All.end(); ++it){
			out << (*it).getDescription() << "; ";

			//			if ((*it).getDateStart().day != -1 && (*it).getDateEnd().day != -1) {
			if ((*it).getDateStart().day < 10){
				out << "0" << (*it).getDateStart().day;
			}
			else out << (*it).getDateStart().day;

			if ((*it).getDateStart().month < 10){
				out << "0" << (*it).getDateStart().month;
			}
			else out << (*it).getDateStart().month;

			if ((*it).getDateStart().year < 10){
				out << "0" << (*it).getDateStart().year;
			}
			else out << (*it).getDateStart().year;

			out << " to ";

			if ((*it).getDateEnd().day < 10){
				out << "0" << (*it).getDateEnd().day;
			}
			else out << (*it).getDateEnd().day;

			if ((*it).getDateEnd().month < 10){
				out << "0" << (*it).getDateEnd().month;
			}
			else out << (*it).getDateEnd().month;

			if ((*it).getDateEnd().year < 10){
				out << "0" << (*it).getDateEnd().year;
			}
			else out << (*it).getDateEnd().year;

			out << " ;";


			//			}
			// don't edit this part. its not finished. going to add more

			if ((*it).getTimeEnd() != -1) {
				if ((*it).getTimeStart() < 1000){
					out << "0" << (*it).getTimeStart();
				}
				else out << (*it).getTimeStart();

				out << " to ";
			}

			if ((*it).getTimeStart() != -1){
				if ((*it).getTimeEnd() < 1000){
					out << "0" << (*it).getTimeEnd();
				}
				out << (*it).getTimeEnd();
			}



			if ((*it).getImportance()){
				out << " #impt";
			}
			out << "\r\n";

		}
	}
	else out << "The list is empty!" << endl;

	return out.str();

}

string Planner::toString(string nameOfList){
	//convert the list to a string and return
	string finalString;
	if (nameOfList == "Home"){
		finalString = HomeListToString();
		return finalString;
	}
	else if (nameOfList == "Upcoming"){
		finalString = upcomingListToString();
		return finalString;
	}
	else if (nameOfList == "Missed"){
		finalString = missedListToString();
		return finalString;
	}
	else if (nameOfList == "searchList"){
		finalString = searchListToString();
		return finalString;
	}
}

string Planner::statusToString(string command, Task theTask){
	string finalString;
	if (command == "add"){
		finalString = addStatusToString(theTask);
		return finalString;
	}
	else if (command == "delete"){
		finalString = deleteStatusToString(theTask);
		return finalString;
	}
	else if (command == "edit"){
		finalString = editStatusToString();
		return finalString;
	}
	else if (command == "undo"){
		finalString = undoStatusToString();
		return finalString;
	}
	else if (command == "clear"){
		finalString = clearStatusToString();
		return finalString;
	}
	else if (command == "save"){
		finalString = saveStatusToString();
		return finalString;
	}
}

string Planner::addStatusToString(Task theTask){

	ostringstream out;
	out << "Task added: ";

	out << theTask.getDescription() << " ";

	switch (theTask.getNumOfDates()){
	case 0:
		break;
	case 1:
		out << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
		break;
	case 2:
		out << theTask.getDateStart().day << "/" << theTask.getDateStart().month << "/" << theTask.getDateStart().year << " to ";
		out << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
		break;
	}

	switch (theTask.getNumOfTimes()){
	case 0:
		break;
	case 1:
		out << theTask.getTimeStart();
		break;
	case 2:
		out << theTask.getTimeStart() << " to ";
		out << theTask.getTimeEnd();
		break;
	default:
		cout << "fatal error!";
	}



	if (theTask.getImportance()){
		out << " #impt";
	}

	out << "\r\n";

	return out.str();
}

string Planner::deleteStatusToString(Task theTask){
	ostringstream out;
	out << "Task deleted : ";

	out << theTask.getDescription() << " ";

	switch (theTask.getNumOfDates()){
	case 0:
		break;
	case 1:
		out << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
		break;
	case 2:
		out << theTask.getDateStart().day << "/" << theTask.getDateStart().month << "/" << theTask.getDateStart().year << " to ";
		out << theTask.getDateEnd().day << "/" << theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
		break;
	}

	switch (theTask.getNumOfTimes()){
	case 0:
		break;
	case 1:
		out << theTask.getTimeStart();
		break;
	case 2:
		out << theTask.getTimeStart() << " to ";
		out << theTask.getTimeEnd();
		break;
	default:
		cout << "fatal error!";
	}


	if (theTask.getImportance()){
		out << " #impt";
	}

	out << "\r\n";

	return out.str();
}

string Planner::editStatusToString(){ // to be completed after undo edit works
	ostringstream out;
	out << "The following Task : \r\n";
	out << lastEdit.deletedTask.getDescription() << " ";

	switch (lastEdit.deletedTask.getNumOfDates()){
	case 0:
		break;
	case 1:
		out << lastEdit.deletedTask.getDateEnd().day << "/" << lastEdit.deletedTask.getDateEnd().month << "/" << lastEdit.deletedTask.getDateEnd().year << " ";
		break;
	case 2:
		out << lastEdit.deletedTask.getDateStart().day << "/" << lastEdit.deletedTask.getDateStart().month << "/" << lastEdit.deletedTask.getDateStart().year << " to ";
		out << lastEdit.deletedTask.getDateEnd().day << "/" << lastEdit.deletedTask.getDateEnd().month << "/" << lastEdit.deletedTask.getDateEnd().year << " ";
		break;
	}

	switch (lastEdit.deletedTask.getNumOfTimes()){
	case 0:
		break;
	case 1:
		out << lastEdit.deletedTask.getTimeStart();
		break;
	case 2:
		out << lastEdit.deletedTask.getTimeStart() << " to ";
		out << lastEdit.deletedTask.getTimeEnd();
		break;
	default:
		cout << "fatal error!";
	}


	if (lastEdit.deletedTask.getImportance()){
		out << " #impt";
	}

	out << "\r\nhas been edited to :\r\n";


	out << lastEdit.addedTask.getDescription() << " ";

	switch (lastEdit.addedTask.getNumOfDates()){
	case 0:
		break;
	case 1:
		out << lastEdit.addedTask.getDateEnd().day << "/" << lastEdit.addedTask.getDateEnd().month << "/" << lastEdit.addedTask.getDateEnd().year << " ";
		break;
	case 2:
		out << lastEdit.addedTask.getDateStart().day << "/" << lastEdit.addedTask.getDateStart().month << "/" << lastEdit.addedTask.getDateStart().year << " to ";
		out << lastEdit.addedTask.getDateEnd().day << "/" << lastEdit.addedTask.getDateEnd().month << "/" << lastEdit.addedTask.getDateEnd().year << " ";
		break;
	}

	switch (lastEdit.addedTask.getNumOfTimes()){
	case 0:
		break;
	case 1:
		out << lastEdit.addedTask.getTimeStart();
		break;
	case 2:
		out << lastEdit.addedTask.getTimeStart() << " to ";
		out << lastEdit.addedTask.getTimeEnd();
		break;
	default:
		cout << "fatal error!";
	}

	if (lastEdit.addedTask.getImportance()){
		out << " #impt";
	}


	return out.str();
}

string Planner::undoStatusToString(){ //needs severe refactoring
	ostringstream out;

	if (lastEntry.lastCommand == "add"){
		out << "The following Task has been added back: \r\n";
		out << lastEntry.lastTask.getDescription() << " ";

		switch (lastEntry.lastTask.getNumOfDates()){
		case 0:
			break;
		case 1:
			out << lastEntry.lastTask.getDateEnd().day << "/" << lastEntry.lastTask.getDateEnd().month << "/" << lastEntry.lastTask.getDateEnd().year << " ";
			break;
		case 2:
			out << lastEntry.lastTask.getDateStart().day << "/" << lastEntry.lastTask.getDateStart().month << "/" << lastEntry.lastTask.getDateStart().year << " to ";
			out << lastEntry.lastTask.getDateEnd().day << "/" << lastEntry.lastTask.getDateEnd().month << "/" << lastEntry.lastTask.getDateEnd().year << " ";
			break;
		}

		switch (lastEntry.lastTask.getNumOfTimes()){
		case 0:
			break;
		case 1:
			out << lastEntry.lastTask.getTimeStart();
			break;
		case 2:
			out << lastEntry.lastTask.getTimeStart() << " to ";
			out << lastEntry.lastTask.getTimeEnd();
			break;
		default:
			cout << "fatal error!";
		}


		if (lastEntry.lastTask.getImportance()){
			out << " #impt";
		}

	}
	else if (lastEntry.lastCommand == "delete"){
		out << "The following Task has been removed: \r\n";
		out << lastEntry.lastTask.getDescription() << " ";

		switch (lastEntry.lastTask.getNumOfDates()){
		case 0:
			break;
		case 1:
			out << lastEntry.lastTask.getDateEnd().day << "/" << lastEntry.lastTask.getDateEnd().month << "/" << lastEntry.lastTask.getDateEnd().year << " ";
			break;
		case 2:
			out << lastEntry.lastTask.getDateStart().day << "/" << lastEntry.lastTask.getDateStart().month << "/" << lastEntry.lastTask.getDateStart().year << " to ";
			out << lastEntry.lastTask.getDateEnd().day << "/" << lastEntry.lastTask.getDateEnd().month << "/" << lastEntry.lastTask.getDateEnd().year << " ";
			break;
		}

		switch (lastEntry.lastTask.getNumOfTimes()){
		case 0:
			break;
		case 1:
			out << lastEntry.lastTask.getTimeStart();
			break;
		case 2:
			out << lastEntry.lastTask.getTimeStart() << " to ";
			out << lastEntry.lastTask.getTimeEnd();
			break;
		default:
			cout << "fatal error!";
		}


		if (lastEntry.lastTask.getImportance()){
			out << " #impt";
		}


	}
	else if (lastEntry.lastCommand == "edit"){ // will do this after undo edit works
		out << "The following Task : \r\n";
		out << lastEdit.addedTask.getDescription() << " ";

		switch (lastEdit.addedTask.getNumOfDates()){
		case 0:
			break;
		case 1:
			out << lastEdit.addedTask.getDateEnd().day << "/" << lastEdit.addedTask.getDateEnd().month << "/" << lastEdit.addedTask.getDateEnd().year << " ";
			break;
		case 2:
			out << lastEdit.addedTask.getDateStart().day << "/" << lastEdit.addedTask.getDateStart().month << "/" << lastEdit.addedTask.getDateStart().year << " to ";
			out << lastEdit.addedTask.getDateEnd().day << "/" << lastEdit.addedTask.getDateEnd().month << "/" << lastEdit.addedTask.getDateEnd().year << " ";
			break;
		}

		switch (lastEdit.addedTask.getNumOfTimes()){
		case 0:
			break;
		case 1:
			out << lastEdit.addedTask.getTimeStart();
			break;
		case 2:
			out << lastEdit.addedTask.getTimeStart() << " to ";
			out << lastEdit.addedTask.getTimeEnd();
			break;
		default:
			cout << "fatal error!";
		}


		if (lastEdit.addedTask.getImportance()){
			out << " #impt";
		}

		out << "\r\n has been edited to \r\n";

		out << lastEdit.deletedTask.getDescription() << " ";

		switch (lastEdit.deletedTask.getNumOfDates()){
		case 0:
			break;
		case 1:
			out << lastEdit.deletedTask.getDateEnd().day << "/" << lastEdit.deletedTask.getDateEnd().month << "/" << lastEdit.deletedTask.getDateEnd().year << " ";
			break;
		case 2:
			out << lastEdit.deletedTask.getDateStart().day << "/" << lastEdit.deletedTask.getDateStart().month << "/" << lastEdit.deletedTask.getDateStart().year << " to ";
			out << lastEdit.deletedTask.getDateEnd().day << "/" << lastEdit.deletedTask.getDateEnd().month << "/" << lastEdit.deletedTask.getDateEnd().year << " ";
			break;
		}

		switch (lastEdit.deletedTask.getNumOfTimes()){
		case 0:
			break;
		case 1:
			out << lastEdit.deletedTask.getTimeStart();
			break;
		case 2:
			out << lastEdit.deletedTask.getTimeStart() << " to ";
			out << lastEdit.deletedTask.getTimeEnd();
			break;
		default:
			cout << "fatal error!";
		}


		if (lastEdit.deletedTask.getImportance()){
			out << " #impt";
		}

	}
	return out.str();
}

string Planner::clearStatusToString(){
	return "All content cleared. \r\n";
}

string Planner::saveStatusToString(){
	return "File has been saved. \r\n";
}

int Planner::getIdOfLastEntry(void){// act this function returns id not last entry, need to change name

	int n;

	static int idGeneratror;
	if (All.empty()){
		idGeneratror = 10001;
	}
	else idGeneratror++;
	return idGeneratror;
}

string Planner::deleteTask(int serialNumber, string nameOfList){
	int idNumber;
	string status;
	list<Task> ::iterator iter;

	if (nameOfList == "Home"){
		iter = HomeList.begin();
		for (int i = 1; i != serialNumber; i++){
			iter++;
		}
		idNumber = (*iter).getIdNumber();

		status = deleteIndex(idNumber);
	}
	else if (nameOfList == "Missed"){
		iter = MissedList.begin();
		for (int i = 1; i != serialNumber; i++){
			iter++;
		}
		idNumber = (*iter).getIdNumber();

		status = deleteIndex(idNumber);
	}
	else if (nameOfList == "Upcoming"){
		iter = UpcomingList.begin();
		for (int i = 1; i != serialNumber; i++){
			iter++;
		}
		idNumber = (*iter).getIdNumber();

		status = deleteIndex(idNumber);
	}
	else cout << "error! name of list is invalid" << endl;
	return status;
}

string Planner::deleteIndex(int idNumber){
	list<Task> ::iterator iter1, iter2;
	iter1 = All.begin();
	for (iter1 = All.begin(); iter1 != All.end(); ++iter1){
		if ((*iter1).getIdNumber() == idNumber){
			iter2 = iter1;
		}
	}
	lastEntry.lastTask = *iter2;
	lastEntry.lastCommand = "delete";
	string status;
	status = statusToString("delete", *iter2);
	All.erase(iter2);

	generateAllOtherList();
	//logging
	stringstream message;
	message << "ID of deleted entry is " << idNumber;
	LogData.addLog("UPDATE", message.str());

	return status;

}

string Planner::undo(void){
	if (lastEntry.lastCommand == "add"){
		int lastEntryID = getIdOfLastEntry() - 1;
		deleteIndex(lastEntryID);
	}
	else if (lastEntry.lastCommand == "delete"){
		addTask(lastEntry.lastTask);
	}
	else if (lastEntry.lastCommand == "edit"){
		deleteIndex(lastEdit.addedTask.getIdNumber());
		addTask(lastEdit.deletedTask);
	}
	string status;
	status = undoStatusToString();
	generateAllOtherList();
	return status;
}

string Planner::clear(void){
	All.clear();
	generateAllOtherList();
	LogData.addLog("UPDATE", "ALL entries cleared ");
	return clearStatusToString();
}

string Planner::editTask(int serialNumber, string nameOfList, string input){
	Task newTask;
	newTask.addDetails(input);
	deleteTask(serialNumber, nameOfList);
	lastEdit.deletedTask = lastEntry.lastTask;
	addTask(newTask);
	lastEdit.addedTask = lastEntry.lastTask;
	lastEntry.lastCommand = "edit";
	generateAllOtherList();
	LogData.addLog("UPDATE", "Edit Taken Place ");
	return editStatusToString();
}

string Planner::save(string fileName){
	ofstream write(fileName);
	string allTasks;
	allTasks = saveDataToString();
	write << allTasks;
	write.close();
	LogData.addLog("UPDATE", "File Save Operation");
	return saveStatusToString();
}

string Planner::AllToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = All.begin();
	int serialNumber = 1;
	int entryCount = 0;
	if (!All.empty()){
		for (it = All.begin(); it != All.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";

			switch ((*it).getNumOfDates()){
			case 0:
				break;
			case 1:
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			case 2:
				out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			}

			switch ((*it).getNumOfTimes()){
			case 0:
				break;
			case 1:
				out << (*it).getTimeStart();
				break;
			case 2:
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
				break;
			default:
				cout << "fatal error!";
			}

			if ((*it).getImportance()){
				out << " #impt";
			}

			out << "\r\n";
			serialNumber = serialNumber + 1;
			entryCount++;
		}
	}
	else {
		out << "The list is empty!" << endl;
	}
	return out.str();
}

string Planner::HomeListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = HomeList.begin();
	int serialNumber = 1;
	if (!HomeList.empty()){
		for (it = HomeList.begin(); it != HomeList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";

			switch ((*it).getNumOfDates()){
			case 0:
				break;
			case 1:
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			case 2:
				out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			}

			switch ((*it).getNumOfTimes()){
			case 0:
				break;
			case 1:
				out << (*it).getTimeStart();
				break;
			case 2:
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
				break;
			default:
				cout << "fatal error!";
			}


			if ((*it).getImportance()){
				out << " #impt";
			}

			out << "\r\n";
			serialNumber = serialNumber + 1;
		}
	}
	else out << "The list is empty!" << endl;

	return out.str();
}

string Planner::upcomingListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = UpcomingList.begin();
	int serialNumber = 1;
	if (!UpcomingList.empty()){
		for (it = UpcomingList.begin(); it != UpcomingList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";

			switch ((*it).getNumOfDates()){
			case 0:
				break;
			case 1:
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			case 2:
				out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			}

			switch ((*it).getNumOfTimes()){
			case 0:
				break;
			case 1:
				out << (*it).getTimeStart();
				break;
			case 2:
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
				break;
			default:
				cout << "fatal error!";
			}


			if ((*it).getImportance()){
				out << " #impt";
			}

			out << "\r\n";
			serialNumber = serialNumber + 1;
		}
	}
	else out << "The list is empty!" << endl;

	return out.str();
}

string Planner::missedListToString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = MissedList.begin();
	int serialNumber = 1;
	if (!MissedList.empty()){
		for (it = MissedList.begin(); it != MissedList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";

			switch ((*it).getNumOfDates()){
			case 0:
				break;
			case 1:
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			case 2:
				out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			}

			switch ((*it).getNumOfTimes()){
			case 0:
				break;
			case 1:
				out << (*it).getTimeStart();
				break;
			case 2:
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
				break;
			default:
				cout << "fatal error!";
			}


			if ((*it).getImportance()){
				out << " #impt";
			}

			out << "\r\n";
			serialNumber = serialNumber + 1;
		}
	}
	else out << "The list is empty!" << endl;

	return out.str();
}

string Planner::searchListToString(void){

	ostringstream out;
	list<Task> ::iterator it;
	it = searchList.begin();
	int serialNumber = 1;
	if (!searchList.empty()){
		for (it = searchList.begin(); it != searchList.end(); ++it){
			out << serialNumber << ". " << (*it).getDescription() << " ";

			switch ((*it).getNumOfDates()){
			case 0:
				break;
			case 1:
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			case 2:
				out << (*it).getDateStart().day << "/" << (*it).getDateStart().month << "/" << (*it).getDateStart().year << " to ";
				out << (*it).getDateEnd().day << "/" << (*it).getDateEnd().month << "/" << (*it).getDateEnd().year << " ";
				break;
			}

			switch ((*it).getNumOfTimes()){
			case 0:
				break;
			case 1:
				out << (*it).getTimeStart();
				break;
			case 2:
				out << (*it).getTimeStart() << " to ";
				out << (*it).getTimeEnd();
				break;
			default:
				cout << "fatal error!";
			}

			out << " " << (*it).getIdNumber();			//remember to remove

			if ((*it).getImportance()){
				out << " #impt";
			}

			out << "\r\n";
			serialNumber = serialNumber + 1;
		}
	}
	else out << "The list is empty!" << endl;

	return out.str();
}

void Planner::generateAllOtherList(void){
	HomeList.clear();
	MissedList.clear();
	UpcomingList.clear();
	generateHomeList();
	generateMissedList();
	generateUpcomingList();
}

void Planner::generateHomeList(void){
	list<Task> ::iterator it;

	for (it = All.begin(); it != All.end(); ++it){
		if (isHome(currentDate, it)) {
			HomeList.push_back(*it);
		}
	}
}
//assumes 30 days in a month
bool Planner::isHome(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinHome = false;
	//case 1: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateEnd().month == (currentDate.month)) {
			if ((*it).getDateEnd().day <= (currentDate.day + 7) && (*it).getDateEnd().day >= currentDate.day) {
				if ((*it).getDateEnd().year == currentDate.year) {
					isWithinHome = true;
				}
			}
		}
	}
	//case 2: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateEnd().month == (currentDate.month)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day <= 31 && (*it).getDateEnd().day >= currentDate.day) {
				isWithinHome = true;
			}
		}
	}
	//case 3:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateEnd().month == (currentDate.month + 1)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day < (30 - currentDate.day)) {
				isWithinHome = true;
			}
		}
	}
	//case 4: current date + 7 days = next month, december
	else if ((*it).getDateEnd().year == (currentDate.year + 1)) {
		if ((*it).getDateEnd().month == 1) {
			if ((*it).getDateEnd().day < (30 - currentDate.day)) {
				isWithinHome = true;
			}
		}
	}

	return isWithinHome;
}

void Planner::generateMissedList(void){
	list<Task> ::iterator iter;

	for (iter = All.begin(); iter != All.end(); ++iter){
		if (isMissed(currentDate, iter)) {
			MissedList.push_back(*iter);
		}
	}
}

bool Planner::isMissed(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinMissed = false;
	//case 1: passed year
	if ((*it).getDateEnd().year < currentDate.year) {
		isWithinMissed = true;
	}
	//case 2: same year, passed month
	else if ((*it).getDateEnd().year == currentDate.year) {
		if ((*it).getDateEnd().month < currentDate.month) {
			isWithinMissed = true;
		}//case 3: same year, same month, passed day
		else if ((*it).getDateEnd().month == currentDate.month) {
			if ((*it).getDateEnd().day < currentDate.day) {
				isWithinMissed = true;
			}
		}
	}

	return isWithinMissed;
}

void Planner::generateUpcomingList(void){
	list<Task> ::iterator iter;

	for (iter = All.begin(); iter != All.end(); ++iter){
		if (isUpcoming(currentDate, iter)) {
			UpcomingList.push_back(*iter);
		}
	}
}

bool Planner::isUpcoming(taskDate currentDate, list<Task>::iterator it){
	bool isWithinUpcoming = true;

	//case 1-4 to check if entry should be within home

	//case 1: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateEnd().month == (currentDate.month)) {
			if ((*it).getDateEnd().day <= (currentDate.day + 7) && (*it).getDateEnd().day >= currentDate.day) {
				if ((*it).getDateEnd().year == currentDate.year) {
					isWithinUpcoming = false;
				}
			}
		}
	}
	//case 2: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateEnd().month == (currentDate.month)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day <= 31 && (*it).getDateEnd().day >= currentDate.day) {
				isWithinUpcoming = false;
			}
		}
	}
	//case 3:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateEnd().month == (currentDate.month + 1)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day < (30 - currentDate.day)) {
				isWithinUpcoming = false;
			}
		}
	}
	//case 4: current date + 7 days = next month, december
	else if ((*it).getDateEnd().year == (currentDate.year + 1)) {
		if ((*it).getDateEnd().month == 1) {
			if ((*it).getDateEnd().day < (30 - currentDate.day)) {
				isWithinUpcoming = false;
			}
		}
	}

	// case 5-7 to check if entry should be in missed

	//case 5: passed year
	if ((*it).getDateEnd().year < currentDate.year) {
		isWithinUpcoming = false;
	}
	//case 6: same year, passed month
	else if ((*it).getDateEnd().year == currentDate.year) {
		if ((*it).getDateEnd().month < currentDate.month) {
			isWithinUpcoming = false;
		}//case 7: same year, same month, passed day
		else if ((*it).getDateEnd().month == currentDate.month) {
			if ((*it).getDateEnd().day < currentDate.day) {
				isWithinUpcoming = false;
			}
		}
	}

	return isWithinUpcoming;
}

void Planner::generateSearchList(string target){
	list<Task> ::iterator iter;
	Task tempTask;
	searchList.clear();
	for (iter = All.begin(); iter != All.end(); ++iter){
		tempTask = *iter;
		if (tempTask.isSearchTargetPresent(target)){
			searchList.push_back(tempTask);
		}
	}
}