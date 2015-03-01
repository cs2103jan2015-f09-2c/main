#include "Task.h"
#include <iostream>
#include <string>

using namespace std;

int main(){
	Task test;
	string input;

	getline(cin, input);

	test.addDetails(input);

	cout << test.getDescription() << endl;
	cout << test.getDateStart().day << test.getDateStart().month << test.getDateStart().year << endl;
	cout << test.getDateEnd().day << test.getDateEnd().month << test.getDateEnd().year << endl;
	cout << test.getTimeStart().hour << test.getTimeStart().min << endl;
	cout << test.getTimeEnd().hour << test.getTimeEnd().min << endl;
	cout << test.isImpt() << endl;

	string target;
	cin >> target;
	cout << test.isSearchTargetPresent(target);

	return 0;
}