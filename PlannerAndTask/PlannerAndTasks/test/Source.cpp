#include "Task.h"
#include "Planner.h"
#include<iostream>
using namespace std;
int main(){
	Planner P;
	Task T;
	T.addDetails("meeting at school; date 123456to987654 #impt");
	P.addTask(T);

	return 0;
}