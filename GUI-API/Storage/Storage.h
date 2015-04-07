#pragma once
#include <windows.h>
#include <string>
#include <list>
#include <Shlwapi.h>
#include <atlstr.h>

using namespace std;

const string STATUS_MESSAGE_SAVED_SUCCESSFULLY = "saved successfully to this address: ";
const string DEFAULT_FILE_NAME = "myPlanner.txt";
const string STATUS_MESSAGE_FILE_NOT_FOUND = "file not found";
const string STATUS_MESSAGE_INVALID_FILE_ADDRESS = "invalid save address";

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
	string extractDirectoryFolder(string&);
	bool isFileNameValid(string);
	

public:
	static Storage* getInstanceOfStorage();
	~Storage();
	string retrieveSaveAddress();
	string saveWithFileAddress(string, string);
	string save(string);
	string load();
	string load(string, string&);
	bool isAddressValid(string); //supposed to be in private
};

