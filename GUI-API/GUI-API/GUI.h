#pragma once
#include <string>
#include <vector>

using namespace std;

class GUI
{
public:
	GUI(){
	}

	~GUI(){
	}

	//vector to string converter
	string createString(vector<string> content) {
		string output;

		//--vector to string functions--//

		return output;
	}

	//to process user input. ideally takes in input and pass off to processing function, which will return a new vector. vector then goes through createString now it takes in input and returns input immediately
	string processUserInput(string userInput) {
		vector<string> database;

		//--functions for pulling content--//
		//--process--//
		//--write to database--//

		string output = createString(database);
		//return output;

		return userInput;		//temporary for proof of text entered;
	}

	//to pull information from vector (identified by viewType) and display
	string switchView(string viewType) {
		vector<string> database;

		//--functions for pulling content--//
		//--write to database--//

		string output = createString(database);
		//return output;

		return viewType;		//temporary for proof of switch;
	}
};

