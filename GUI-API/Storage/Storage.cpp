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

Storage::Storage()
{
	retrieveList();
	fileAddress = retrieveFirstAddress();
}


Storage::~Storage()
{
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

string Storage::save(string saveAddress){
	//check if the address is in the list
	bool doesExist = doesAddressAlrdExist(saveAddress);
	if (!doesExist){
		listOfFileAddress.push_front(saveAddress);
	}

	fileAddress = saveAddress;
	string status = save();
	return status;
}

string Storage::save(){
	ofstream write(fileAddress, ios_base::app);
	string status = STATUS_MESSAGE_SAVED_SUCCESSFULLY + fileAddress;
	return status;
}

void Storage::updateContent(string content){
	fileContent = content;
}

string Storage::retrieveSaveAddress() {
	if (fileAddress.empty()){
		fileAddress = DEFAULT_FILE_NAME;
	}

	return fileAddress;
}

bool Storage::doesAddressAlrdExist(string saveAddress){
	list<string>::iterator iter = listOfFileAddress.begin();
	bool isSame = false;

	while (!isSame && iter != listOfFileAddress.end()){
		if (*iter == saveAddress){
			isSame = true;
		}
	}
	return isSame;
}