#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StorageUnitTest{		
	TEST_CLASS(StorageTest){
	public:
		
		TEST_METHOD(SaveWithFileAddressTest){
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

	};
}