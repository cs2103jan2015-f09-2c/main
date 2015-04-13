#pragma once
#include <windows.h>
#include <string>
#include <list>
#include <Shlwapi.h>
#include <atlstr.h>

using namespace std;

class Storage{
private:
	Storage();
	~Storage();

	string fileContent;
	string fileAddress;
	list<string> listOfFileAddress;
	static Storage* myStorage;
	string myList;

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
	string retrieveSaveAddress();
	string saveWithFileAddress(string, string);
	string save(string);
	string load();
	string load(string, string&);
	bool isAddressValid(string); //supposed to be in private
};
