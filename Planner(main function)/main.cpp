//main function acts like a central dispatcher that decides which function to call
//to carry out a certain task

#include <iostream>
#include <string>

void runOperation(std::string);
std::string initiateGUI(std::string);
void processUserInput(std::string);
std::string extractCommand(std::string&);
void processCommand(std::string, std::string);
void processCommandAdd(std::string);
void processCommandDelete(std::string);
void processCommandEdit(std::string);
void processCommandSearch(std::string);
void processCommandChangeview(std::string);
void processCommandClear();
void processCommandExit();
void processCommandHelp();

bool continueOperation = true;

int main(int argc, char *argv[]){
	//the user calls the program by double-clicking the shortcut
	//argc is expected to be 1. Anything different is an error

	std::string view = "next 7 days";
	runOperation(view); 
	return 0;
}

void runOperation(std::string view){
	//run operation with the specified view
	
	//initiate GUI
	std::string userInput = initiateGUI(view);
	processUserInput(userInput);
}

std::string initiateGUI(std::string view){
	//call GUI to display the next 7 days event, an input textbox, relevant buttons and messages
	//GUI collects userInput from the input textbox and return the string input to caller
	//when user changes view, initiateGUI will return the following string: "changeview upcoming" for example
	std::string userInput;
	return userInput;
}

void processUserInput(std::string userInput){
	//identify and isolate the command word: delete, add, search, clear, edit, exit, help, changeview
	//the rest of the userInput is task detail
	
	while (continueOperation){
		std::string command = extractCommand(userInput);
		processCommand(command, userInput);
	}
}

std::string extractCommand(std::string& userInput){
	//extract the first word to be the command and update userInput
	std::string command;
	return command;
}

void processCommand(std::string command, std::string taskDetail){
	if (command == "add"){
		processCommandAdd(taskDetail);
	}

	else
	if (command == "delete"){
		processCommandDelete(taskDetail);
	}

	else
	if (command == "edit"){
		processCommandEdit(taskDetail);
	}

	else
	if (command == "clear"){
		processCommandClear();
	}

	else
	if (command == "search"){
		processCommandSearch(taskDetail);
	}

	else
	if (command == "help"){
		processCommandHelp();
	}


	else
	if (command == "changeview"){
		processCommandChangeview(taskDetail);
	}

	else
	if (command == "exit"){
		processCommandExit();
	}
}

void processCommandChangeview(std::string view){
	runOperation(view);
}