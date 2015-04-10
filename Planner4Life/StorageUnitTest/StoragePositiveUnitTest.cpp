#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageUnitTest{
	TEST_CLASS(StorageTest){
public:

	/************************************************************************************************

	Save Unit Tests

	************************************************************************************************/

	TEST_METHOD(testSave_fileAddress){
		//save content to a valid file address
		// \\t\est is used to prevent the system from tabbing
		Storage* myTestStorage;
		myTestStorage = Storage::getInstanceOfStorage();
		string saveAddress = "D:\\saveFile.txt";			
		string expectedContent = "test";
		string actualOutcome = myTestStorage->saveWithFileAddress(saveAddress, expectedContent);
		string expectedOutcome = "saved successfully to this address: D:\\saveFile.txt";
		Assert::AreEqual(expectedOutcome, actualOutcome);
		
		ifstream read(saveAddress);
		string actualContent;
		getline(read, actualContent);
		Assert::AreEqual(expectedContent, actualContent);
	
	}

	TEST_METHOD(testSave_valid_address){
		//file address specified does not exist
		Storage* myTestStorage;
		myTestStorage = Storage::getInstanceOfStorage();
		string saveAddress = "D:\\testsave.txt";
		bool actualOutcome = myTestStorage->isAddressValid(saveAddress);
		Assert::IsTrue(actualOutcome);
	}


	TEST_METHOD(testSave_invalid_address_1){
		//file address does not have .txt file
		Storage* myTestStorage;
		myTestStorage = Storage::getInstanceOfStorage();
		string saveAddress = "C:\\";
		bool actualOutcome = myTestStorage->isAddressValid(saveAddress);
		Assert::IsFalse(actualOutcome);
	}

		TEST_METHOD(testSave_valid_address_2){
		//check whether file address is case sensitive
		Storage* myTestStorage;
		myTestStorage = Storage::getInstanceOfStorage();
		string saveAddress = "d:\\test.txt";
		bool actualOutcome = myTestStorage->isAddressValid(saveAddress);
		Assert::IsTrue(actualOutcome);
	}

	/************************************************************************************************

	Load Unit Tests

	************************************************************************************************/
	TEST_METHOD(testLoad_Storage_valid_outcome){
		//file address specified exist
		Storage* myTestStorage;
		string actualContent;

		myTestStorage = Storage::getInstanceOfStorage();
		string saveAddress = "D:\\saveFile.txt";
		string actualOutcome = myTestStorage->load(saveAddress, actualContent);
		string expectedOutcome = "D:\\saveFile.txt loaded successfully";
		Assert::AreEqual(expectedOutcome, actualOutcome);
	}

	TEST_METHOD(testLoad_Storage_valid_content){
		//file address specified exist
		Storage* myTestStorage;
		myTestStorage = Storage::getInstanceOfStorage();
		string saveAddress = "D:\\saveFile.txt";
		string expectedContent = "test\n";
		string actualContent;
		string actualOutcome = myTestStorage->load(saveAddress, actualContent);
		Assert::AreEqual(expectedContent, actualContent);
	}

	TEST_METHOD(testLoadStorage_invalid){
		//file address specified does not exist
		Storage* myTestStorage;
		myTestStorage = Storage::getInstanceOfStorage();
		string actualContent;
		string saveAddress = "testWrongFileName.txt";
		string actualOutcome = myTestStorage->load(saveAddress, actualContent);
		string expectedOutcome = "file not found";
		Assert::AreEqual(expectedOutcome, actualOutcome);
	}
	};
}