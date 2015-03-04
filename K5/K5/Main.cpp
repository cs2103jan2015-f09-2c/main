#include "Planner.h"
#include "Task.h"
#include<iostream>
#include<string>
#include<list>
#include <ctime>

using namespace std;
int main(){
	Task T;
	Planner P;
	T.addDetails("meeting school; date 123456to987654; #impt");
	P.addTask(T);
	cout<<P.toString("allTaskList");
	system("pause");
	return 0;
	}