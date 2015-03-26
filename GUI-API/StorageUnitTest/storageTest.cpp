#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageUnitTest{		
	TEST_CLASS(StorageTest){
	public:
		
		TEST_METHOD(SaveWithFileAddressTest){
		//save content to a valid file address
			Storage* myTestStorage;
			myTestStorage = Storage::getInstanceOfStorage();
			string saveAddress = "D:\hello.txt";
			string expectedContent = "test";
			string actualOutcome = myTestStorage->saveWithFileAddress(saveAddress, expectedContent);
			string expectedOutcome = "saved successfully to this address: D:\hello.txt";
			Assert::AreEqual(expectedOutcome, actualOutcome);

			ifstream read(saveAddress);
			string actualContent;
			getline(read, actualContent);
			Assert::AreEqual(expectedContent, actualContent);
		}

		TEST_METHOD(loadTest){
		//file address specified exist
			Storage* myTestStorage;
			myTestStorage = Storage::getInstanceOfStorage();
			string saveAddress = "D:\hello.txt";
			string expectedContent = "test\n";
			string actualContent;
			string actualOutcome = myTestStorage->load(saveAddress, actualContent);
			string expectedOutcome = "D:\hello.txt loaded successfully";
			Assert::AreEqual(expectedOutcome, actualOutcome);
			Assert::AreEqual(expectedContent, actualContent);
		}

		TEST_METHOD(invalidLoadTest){
		//file address specified does not exist
			Storage* myTestStorage;
			myTestStorage = Storage::getInstanceOfStorage();
			string actualContent;
			string saveAddress = "D:\wrong.txt";
			string actualOutcome = myTestStorage->load(saveAddress, actualContent);
			string expectedOutcome = "file not found";
			Assert::AreEqual(expectedOutcome, actualOutcome);
		}
	};
}