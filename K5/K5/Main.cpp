#include "Planner.h"
#include "Task.h"
#include<iostream>
#include<string>
#include<list>
#include <ctime>

using namespace std;
int main(){
	Task T1,T2,T3,T4;
	Planner P;
	T1.addDetails("meeting school; date 020415 to 020415; time 1500 to 1630 #impt");
	T2.addDetails("go office; date 010115 to 010115; time 1700 to 1830");
//	T3.addDetails("do homework school; date 150415 to 170415; 1900 to 1930 #impt");    this is super weird. dunno why this task cannot add!
	T4.addDetails("meet friends; date 230215 to 230215; time 1500 to 1630");
	P.addTask(T1);
	P.addTask(T2);
//	P.addTask(T3);
	P.addTask(T4);
	cout<<P.toString("allTaskList");
	system("pause");
	return 0;
	}