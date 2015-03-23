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
	ofstream write(myList);
	if (!listOfFileAddress.empty()){
		list<string>::iterator iter = listOfFileAddress.begin();

		for (; iter != listOfFileAddress.end(); iter++){
			write << (*iter);
		}
	}

	write.close();
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
	bool doesExist = doesAddressAlrdExist(saveAddress);
	if (!doesExist){
		listOfFileAddress.push_front(saveAddress);
	}

	fileAddress = saveAddress;
	string status = save(content);
	return status;
}

string Storage::save(string content){
	updateContent(content);
	ofstream write(fileAddress/*, ios_base::app*/);
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
	list<string>::iterator iter;
	if (isListEmpty()){
		iter = listOfFileAddress.begin();
	}
	
	bool isSame = false;

	for (iter = listOfFileAddress.begin(); !isSame && iter != listOfFileAddress.end(); ++iter){
		if ((*iter) == saveAddress){
			isSame = true;
		}
	}
	return isSame;
}