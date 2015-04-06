#pragma once
#include <string>
#include <list>
using namespace std;

const string STATUS_MESSAGE_SAVED_SUCCESSFULLY = "saved successfully to this address: ";
const string DEFAULT_FILE_NAME = "myPlanner.txt";
const string STATUS_MESSAGE_FILE_NOT_FOUND = "file not found";

class Storage{
private:
	string fileContent;
	string fileAddress;
	//string fileName;
	list<string> listOfFileAddress;
	Storage();
	static Storage* myStorage;
	const string myList = "saveLocationList.txt";
	void retrieveList();
	bool isListEmpty() const;
	string retrieveFirstAddress();
	bool doesAddressAlrdExist(string);
	void updateContent(string);
	void updateMyList();

public:
	static Storage* getInstanceOfStorage();
	~Storage();
	string retrieveSaveAddress();
	string saveWithFileAddress(string, string);
	string save(string);
	string load();
	string load(string, string&);
};

