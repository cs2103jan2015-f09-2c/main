#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskUnitTest
{
	TEST_CLASS(TaskUnitTest)
	{
	public:

		/************************************************************************************************

		Description Unit Tests

		************************************************************************************************/
		//@author A0111314A
		TEST_METHOD(testAddDetails_Description_normal){
			Task testTask;
			string testDescription = "Meeting in school";

			testTask.addDetails("Meeting in school; date 270315 to 290315; time 1300 to 1500");

			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		TEST_METHOD(testAddDetails_Description_whitespace){
			Task testTask;
			string testDescription = "  ";

			testTask.addDetails("  ; date 270315 to 290315; time 1300 to 1500");

			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		TEST_METHOD(testAddDetails_Description_blankDelimiter){
			Task testTask;
			string testDescription = "";

			testTask.addDetails("; date 270315 to 290315; time 1300 to 1500");

			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		/************************************************************************************************

		Date Unit Tests

		************************************************************************************************/

		TEST_METHOD(testStoreStartDate_Date_startDay){
			taskDate dateStartControl;
			Task testTask;

			dateStartControl.day = 15;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateStartControl.day, testTask.getDateStart().day);
		}

		TEST_METHOD(testStoreStartDate_Date_startMonth){
			taskDate dateStartControl;
			Task testTask;

			dateStartControl.month = 3;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateStartControl.month, testTask.getDateStart().month);
		}

		TEST_METHOD(testStoreStartDate_Date_startYear){
			taskDate dateStartControl;
			Task testTask;

			dateStartControl.year = 15;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateStartControl.year, testTask.getDateStart().year);
		}

		TEST_METHOD(testStoreEndDate_Date_EndDay){
			taskDate dateEndControl;
			Task testTask;

			dateEndControl.day = 16;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.day, testTask.getDateEnd().day);
		}

		TEST_METHOD(testStoreEndDate_Date_EndMonth){
			taskDate dateEndControl;
			Task testTask;

			dateEndControl.month = 4;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.month, testTask.getDateEnd().month);
		}

		TEST_METHOD(testStoreEndDate_Date_EndYear){
			taskDate dateEndControl;
			Task testTask;

			dateEndControl.year = 16;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.year, testTask.getDateEnd().year);
		}

		TEST_METHOD(testProcessDate_Date_oneDate){
			Task testTask;
			bool isOneDate = false;

			testTask.addDetails("Meeting in school; date 150315; time 1300 to 1500");

			if (testTask.getNumOfDates() == 1){
				isOneDate = true;
			}

			Assert::IsTrue(isOneDate);
		}

		TEST_METHOD(testProcessDate_Date_noDate){
			Task testTask;
			bool isNoDate;

			testTask.addDetails("Meeting in school; time 1300 to 1500");

			if (testTask.getDateStart().year == -1 && testTask.getDateStart().month == -1 && testTask.getDateStart().day == -1){
				if (testTask.getDateEnd().year == -1 && testTask.getDateEnd().month == -1 && testTask.getDateEnd().day == -1){
					isNoDate = true;
				}
			}

			Assert::IsTrue(isNoDate);
		}

		//boundary case for positive value partition: 3 digits in each date field
		//boundary case for positive value partition: 1 digit in each field;
		//Partition for negative dates
		//Partition for switch of start and end date

		/************************************************************************************************

		Time Unit Tests

		************************************************************************************************/

		TEST_METHOD(testProcessTime_Time_Start){
			Task testTask;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(testTask.getTimeStart(), 1300);
		}

		TEST_METHOD(testProcessTime_Time_End){
			Task testTask;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(testTask.getTimeEnd(), 1500);
		}

		TEST_METHOD(testProcessTime_Time_oneTime){
			Task testTask;
			bool isOneTime;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300");

			if (testTask.getTimeEnd() == -1) {
				if (testTask.getTimeStart() == 1300) {
					isOneTime = true;
				}
			}

			Assert::IsTrue(isOneTime);
		}

		TEST_METHOD(testProcessTime_Time_noTime){
			Task testTask;
			bool isNoTime;

			testTask.addDetails("Meeting in school; date 150315 to 160416");

			if (testTask.getTimeEnd() == -1) {
				if (testTask.getTimeStart() == -1) {
					isNoTime = true;
				}
			}

			Assert::IsTrue(isNoTime);
		}


		/************************************************************************************************

		Search Unit Tests

		************************************************************************************************/

		//@author karthik
		TEST_METHOD(testIsSearchTargetPresent_Positive){
			Task testTask;
			string positiveSearchTarget = "meeting", negativeSearchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsTrue(testTask.isSearchTargetPresent(positiveSearchTarget));
		}

		TEST_METHOD(testIsSearchTargetPresent_Negative){
			Task testTask;
			string positiveSearchTarget = "meeting", negativeSearchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsFalse(testTask.isSearchTargetPresent(negativeSearchTarget));
		}
	};
}