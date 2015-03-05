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
	T2.addDetails("go office; date 010115 to 010115; time 1700 to 1830");
	T3.addDetails("do homework; date 150415 to 170415; time 1900 to 1930 #impt");   // this is super weird. dunno why this task cannot add!
	T4.addDetails("meet friends; date 230215 to 230215; time 1500 to 1630");
	T5.addDetails("meet friends; date 230215 to 230215; time 900 to 1000");
	T6.addDetails("meet friends; date 230215 to 230215; time 1800 to 1930");
	T7.addDetails("submit CS homework; date 010115 to 010115; time 1700 to 1730");
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
	system("pause");
	return 0;
	}