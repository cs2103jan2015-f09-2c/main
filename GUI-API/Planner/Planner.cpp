#include "Planner.h"
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
	status=statusToString("add", newTask);
	lastEntry.lastCommand = "add";
	lastEntry.lastTask = newTask;

	generateAllOtherList();

	return status;


	//add in the details
	//newTask = content; // i dont know if this correct
	//check time and date
	//taskTime StartTime = newTask._timeStart;
	//taskTime EndTime = newTask._timeEnd;
	//taskDate StartDate = newTask._dateStart;
	//taskDate EndDate = newTask._dateEnd;
	//check for clash
	//bool clash = false;
	//clash=checkForClash(StartTime, EndTime, StartDate, EndDate);
	//if no clash,
	//find spot to enter
	/*int index;
	taskTime startTime, endTime;
	taskDate startDate, endDate;
	startTime = content.getTimeStart();
	endTime = content.getTimeEnd();
	startDate = content.getDateStart();
	endDate = content.getDateEnd();
	if (!clash){
	index = findIndexToSlotIn(startTime, endTime, startDate, endDate);
	}*/

	//enter in to the list
	//list<Task>::iterator it = allTaskList.begin();
	//for (int i = 0; i < index; i++){
	///it++;
	//}
	//allTaskList.insert(it, newTask);
	//generate next7daysList, upcomingList, missedList,
	//generate_next7DaysList();
	//generate_upcomingList();
	//generate_missedList();
	//update the undoData, lastEntry Data Structure
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

			out<< " to ";

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
		finalString = next7DaystoString();
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
		finalString=clearStatusToString();
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
			out << theTask.getDateEnd().day << "/" <<theTask.getDateEnd().month << "/" << theTask.getDateEnd().year << " ";
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

int Planner::getIdOfLastEntry(void){

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
		iter = next7DaysList.begin();
		for (int i = 1; i != serialNumber; i++){
			iter++;
			}
		idNumber = (*iter).getIdNumber();
		
		status=deleteIndex(idNumber);
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
	status=statusToString("delete", *iter2);
	All.erase(iter2);

	generateAllOtherList();

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
	return editStatusToString();
	}

string Planner::save(string fileName){
	ofstream write(fileName);
	string allTasks;
	allTasks = saveDataToString();
	write << allTasks;
	write.close();
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

string Planner::next7DaystoString(void){
	ostringstream out;
	list<Task> ::iterator it;
	it = next7DaysList.begin();
	int serialNumber = 1;
	if (!next7DaysList.empty()){
		for (it = next7DaysList.begin(); it != next7DaysList.end(); ++it){
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
	next7DaysList.clear();
	MissedList.clear();
	UpcomingList.clear();
	generateNext7DaysList();
	generateMissedList();
	generateUpcomingList();
	}

void Planner::generateNext7DaysList(void){
	list<Task> ::iterator it;

	for (it = All.begin(); it != All.end(); ++it){
		if (isNext7Days(currentDate, it)) {
			next7DaysList.push_back(*it);
		}
	}
}
//assumes 30 days in a month
bool Planner::isNext7Days(taskDate currentDate, list<Task>::iterator it) {
	bool isWithinNext7Days = false;
	//case 1: currentDate + 7 days = current month, same year
	if (currentDate.day <= 23) {
		if ((*it).getDateEnd().month == (currentDate.month)) {
			if ((*it).getDateEnd().day <= (currentDate.day + 7) && (*it).getDateEnd().day >= currentDate.day) {
				if ((*it).getDateEnd().year == currentDate.year) {
					isWithinNext7Days = true;
				}
			}
		}
	}
	//case 2: currentDate + 7 days = next month, task = current month, not december
	else if ((*it).getDateEnd().month == (currentDate.month)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day <= 31 && (*it).getDateEnd().day >= currentDate.day) {
				isWithinNext7Days = true;
			}
		}
	}
	//case 3:  currentDate + 7 days = next month, task = next month, not december
	else if ((*it).getDateEnd().month == (currentDate.month + 1)) {
		if ((*it).getDateEnd().year == currentDate.year) {
			if ((*it).getDateEnd().day < (30 - currentDate.day)) {
				isWithinNext7Days = true;
			}
		}
	}
	//case 4: current date + 7 days = next month, december
	else if ((*it).getDateEnd().year == (currentDate.year + 1)) {
		if ((*it).getDateEnd().month == 1) {
			if ((*it).getDateEnd().day < (30 - currentDate.day)) {
				isWithinNext7Days = true;
			}
		}
	}

	return isWithinNext7Days;
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
/*
void Planner::deleteTask(int index){
//find the index
list<taskWithID> ::iterator it = next7DaysList.begin();
for (int i = 0; i < index; i++){
it++;
}
//update the undoData, lastEntry Data Structure
lastEntry.lastCommand == "delete";
lastEntry.lastTask = *it;
//erase the entry at the index
next7DaysList.erase(it);
//generate next7daysList, upcomingList, missedList,
generate_next7DaysList();
generate_upcomingList();
generate_missedList();
}
int Planner::getIndexTodelete(int number, string nameOfList){
//find the ID number in the list
int idNumber;
if (number != 0){
idNumber = findIDNumber(number, nameOfList);
}
else {
idNumber = lastEntry.lastTask.idNumber;
}
//return the index
list<taskWithID> ::iterator it1;
list<taskWithID> ::iterator it2 = next7DaysList.begin();
int index = 0;
for (it1 = next7DaysList.begin(); it1 != next7DaysList.end(); it1++){
if (*it2.IDnumber == number){
return index;
}
else {
it2++;
index++;
}
}
//if  number is 0 means it is an undo. delete the last ID generated
//delete that
}
void Planner::editTask(int number, Task content){
//delete
//add
//update the undoData, lastEntry Data Structure
}
void Planner::undo(void){
//refer to the undoData
if (lastEntry.lastCommand == "add"){
deleteTask(0);
}
else if (lastEntry.lastCommand == "delete"){
addTask(lastEntry.lastTask);
}
else if (lastEntry.lastCommand == "edit"){
deleteTask(0);
addTask(lastEntry.lastTask);
}
else {
cout << "There is nothing to undo." << endl;
}
//do that command with that info
//generate next7daysList, upcomingList, missedList,
generate_next7DaysList();
generate_upcomingList();
generate_missedList();
}
void Planner::clear(void){
//clear the list
allTaskList.clear();
//generate next7daysList, upcomingList, missedList,
generate_next7DaysList();
generate_upcomingList();
generate_missedList();
}
bool Planner::checkForClash(taskDate, taskDate, taskTime, taskTime){
//go to main list
//check for overlaps
//if overlap return true
}
//Functions that generate the next7daysList,
//upcomingList, missedList, searchList
void Planner::generate_next7DaysList(void){
//get today's date
//run down the list, getting each date
//add the events that are in the range
}
void Planner::generate_upcomingList(void){
//get today's date
//find the earliest entry after today
//add in everything till the end of the list, including that entry
}
void Planner::generate_missedList(void){
//get today's date
//find all the dates before today's date
//add in everything till todays date
//when reach today's date, chech the time for today's date events only
//add in those missed by time also
//if no time specified then not considered missed until the next day
}
void Planner::generate_searchList(string target){
//go to start of list
//call the search function inside every entry
//everytime the return is true,add in that entry
}
//other functions
Tdate Planner::getTodaysDate(void){
//use c++ to get current date
time_t t = time(0);
//convert t to Tdate
return convertDate(t);
//return
}
Ttime Planner::getCurrentTime(void){
//use c++ to get current time
time_t t = time(0);
//convert to Ttime
return convertTime(t);
//return
}
int Planner::findIndexToSlotIn(taskDate startDate, taskDate endDate, taskTime startTime, taskTime endTime){
//run down the list
list<taskWithID> ::iterator it = allTaskList.begin();
int index = 0;
//while (it != allTaskList.end()){
//}
return index
//return the index to enter the item
}
int Planner::findIDNumber(int number, string nameofList){
list<taskWithID>::iterator it;
Task tempTask;
//return the ID number associated with the entry
if (nameofList == "allTaskList"){
it = allTaskList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "next7DaysList"){
it = next7DaysList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "upcomingList"){
it = upcomingList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "missedList"){
it = missedList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
else if (nameofList == "searchList"){
it = searchList.begin();
for (int i = 0; i < number; i++){
it++;
}
return *it.IDnumber;
}
}
string Planner::toString(string nameOfList){
//convert the list to a string and return
string finalString;
if (nameOfList == "allTaskList"){
finalString = allTaskListToString();
return finalString;
}
else if (nameOfList == "next7DaysList"){
finalString = next7DaysListToString();
return finalString;
}
else if (nameOfList == "upcomingList"){
finalString = upcomingListToString();
return finalString;
}
else if (nameOfList == "missedList"){
finalString = missedListToString();
return finalString;
}
else if (nameOfList == "searchList"){
finalString = searchListToString();
return finalString;
}
}
string Planner::allTaskListToString(void){
}
string Planner::searchListToString(void){
}*/