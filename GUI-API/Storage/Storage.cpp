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
	string firstAddress = *iter;
	return firstAddress;
}

string Storage::save(string saveAddress){
	//check if the address is in the list
	bool exist = doesAddressAlrdExist(saveAddress);

}

string Storage::retrieveSaveAddress() {
	if (fileAddress.empty()){
		fileAddress = DEFAULT_FILE_NAME;
	}

	return fileAddress;
}