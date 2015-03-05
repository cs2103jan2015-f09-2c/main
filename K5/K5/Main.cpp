#include "Planner.h"
#include "Task.h"
#include<iostream>
#include<string>
#include<list>
#include <ctime>

using namespace std;
int main(){
	Task T1, T2, T3, T4, T5, T6, T7;
	Planner P;
	T1.addDetails("meeting school; date 020415 to 020415; time 1500 to 1630 #impt");
	T2.addDetails("go office; date 010115 to 010115; time 1800 to 1830");
	T3.addDetails("do homework; date 150415 to 170415; time 1900 to 1930 #impt");   // this is super weird. dunno why this task cannot add!
	T4.addDetails("meet friends; date 230215 to 230215; time 1500 to 1630");
	T5.addDetails("meet friends; date 230215 to 230215; time 900 to 1000");
	T6.addDetails("meet friends; date 230215 to 230215; time 1800 to 1930");
	T7.addDetails("submit CS homework; date 010115 to 010115; time 1700 to 1730");
	cout << "Added 7 Tasks: " << endl;
	P.addTask(T1);
	P.addTask(T2);
	P.addTask(T3);
	P.addTask(T4);
	P.addTask(T5);
	P.addTask(T6);
	P.addTask(T7);
	cout<<P.toString("allTaskList");
	cout << endl;
	cout << "after deleting number 2: " << endl;
	P.deleteTask(2,"allTaskList");
	cout << P.toString("allTaskList");
	cout << endl;
	cout << "after undoing delete: " << endl;
	P.undo();
	cout << P.toString("allTaskList");
	Task T8;
	T8.addDetails("dentist appointment; date 140215 to 140215; time 1100 to 1115");
	P.addTask(T8);
	cout << endl;
	cout << "Added Task 8: " << endl;
	cout << P.toString("allTaskList");
	P.undo();
	cout << endl;
	cout << "after undoing add: " << endl;
	cout << P.toString("allTaskList");
	P.editTask(5, "allTaskList", "meet girlfriend; date 230215 to 230215; time 1800 to 1930");
	cout << endl;
	cout << "Edit number 5 : friends to girlfriend: " << endl;
	cout<<P.toString("allTaskList");

	P.clear();
	cout << endl;
	cout << "After clearing the list: " << endl;
	cout << P.toString("allTaskList");

	system("pause");
	return 0;
	}