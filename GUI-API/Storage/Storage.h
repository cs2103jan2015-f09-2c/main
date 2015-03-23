#pragma once
#include <string>
#include <list>
using namespace std;
class Storage{
private:
	string fileContent;
	string fileAddress;
	string fileName;
	list<string> listOfFileAddress;
	Storage();
	static Storage* myStorage;
	const string myList = "myList.txt";
	void retrieveList();
	bool isListEmpty() const;
	string retrieveFirstAddress();

public:
	static const string DEFAULT_FILE_NAME = "myPlanner.txt";
	static Storage* getInstanceOfStorage();
	~Storage();
	string retrieveSaveAddress();
	string save(string);
};

