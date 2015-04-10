//@author A0115934E
#include <fstream>
#include "Storage.h"
Storage* Storage::myStorage = NULL;

void Storage::retrieveList(){
	ifstream read(myList);
	string address;

	while (getline(read, address)){
		listOfFileAddress.push_back(address);
	}
}

Storage::Storage(){
	retrieveList();
	if (!listOfFileAddress.empty()){
		fileAddress = retrieveFirstAddress();
	}

	else {
		fileAddress = DEFAULT_FILE_NAME;
	}
}


Storage::~Storage(){
}

Storage* Storage::getInstanceOfStorage(){
	if (myStorage == NULL){
		myStorage = new Storage();
	}

	return myStorage;
}

bool Storage::isListEmpty() const {
	return listOfFileAddress.empty();
}

string Storage::retrieveFirstAddress(){
	list<string>::iterator iter = listOfFileAddress.begin();
	fileAddress = *iter;
	return fileAddress;
}

string Storage::saveWithFileAddress(string saveAddress, string content){
	//check if the address is in the list
	bool doesExist = false;
	doesExist = doesAddressAlrdExist(saveAddress);
	bool isValid = false;
	string status;

	//if a file address exists in the list, it is a valid address
	if (doesExist) {
		isValid = true;
	}
	else {
		isValid = isAddressValid(saveAddress);
	}

	if (isValid){
		if (!doesExist){
			listOfFileAddress.push_front(saveAddress);
			updateMyList();
		}

		fileAddress = saveAddress;
		status = save(content);
	}

	else{
		status = STATUS_MESSAGE_INVALID_FILE_ADDRESS;
	}

	return status;
}

bool Storage::isAddressValid(string saveAddress){
	bool isValid = false;
	string directory = extractDirectoryFolder(saveAddress);
	string fileName = saveAddress;

	int lengthOfCharArray = directory.length() + 1;
	char * pointerToAddress = new char[lengthOfCharArray];
	strcpy_s(pointerToAddress, lengthOfCharArray, directory.c_str());

	CString address = _T(pointerToAddress);
	if (PathFileExists(address)){
		if (isFileNameValid(fileName)){
			isValid = true;
		}
	}
	return isValid;
}

string Storage::extractDirectoryFolder(string &saveAddress){
	size_t backwardSlashPosition = saveAddress.find_last_of("\\");
	size_t sizeOfDirectory = backwardSlashPosition + 1;
	string directory = saveAddress.substr(0, sizeOfDirectory);

	size_t fileNameStartPos = sizeOfDirectory;
	size_t sizeofSaveAddress = saveAddress.size();
	size_t sizeOfFileName = sizeofSaveAddress - sizeOfDirectory;
	string fileName = saveAddress.substr(fileNameStartPos, sizeOfFileName);
	saveAddress = fileName;
	return directory;
}

bool Storage::isFileNameValid(string fileName){
	bool isValid = false;
	size_t txtPosition = fileName.find(".txt");
	if (txtPosition != string::npos){
		isValid = true;
	}

	return isValid;
}

string Storage::save(string content){
	updateContent(content);
	ofstream write(fileAddress);
	write << fileContent;
	write.close();
	string status = STATUS_MESSAGE_SAVED_SUCCESSFULLY + fileAddress;
	return status;
}

void Storage::updateContent(string content){
	fileContent = content;
}

string Storage::retrieveSaveAddress() {
	return fileAddress;
}

bool Storage::doesAddressAlrdExist(string saveAddress){
	list<string>::iterator listIter;

	bool isSame = false;

	for (listIter = listOfFileAddress.begin(); !isSame && listIter != listOfFileAddress.end(); ++listIter){
		if ((*listIter) == saveAddress){
			isSame = true;
		}
	}
	return isSame;
}

void Storage::updateMyList(){
	ofstream write(myList);
	if (!listOfFileAddress.empty()){
		list<string>::iterator listIter;

		for (listIter = listOfFileAddress.begin(); listIter != listOfFileAddress.end(); ++listIter){
			write << (*listIter) << "\n";
		}
	}

	write.close();
}

string Storage::load(){
	ifstream read(fileAddress);
	string lineContent;
	string allTasks = "";
	while (getline(read, lineContent)){
		allTasks = allTasks + lineContent + "\n";
	}
	return allTasks;
}

string Storage::load(string saveAddress, string& allTasks){
	bool doesExist = doesAddressAlrdExist(saveAddress);
	if (!doesExist){
		return STATUS_MESSAGE_FILE_NOT_FOUND;
	}

	fileAddress = saveAddress;
	allTasks = load();
	string outcome = fileAddress + STATUS_MESSAGE_LOADED_SUCCESSFULLY;
	return outcome;
}