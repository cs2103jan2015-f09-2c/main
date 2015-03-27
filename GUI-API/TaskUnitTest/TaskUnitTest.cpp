#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskUnitTest
{		
	TEST_CLASS(TaskUnitTest)
	{
	public:

		/************************************************************

							Description Unit Tests

		************************************************************/

		//Unit test for functionality of addDetails - Description - normal case
		TEST_METHOD(testAddDetails_Description_normal){
			Task testTask;
			string testDescription = "Meeting in school";
		
			testTask.addDetails("Meeting in school; date 270315 to 290315; time 1300 to 1500");

			//Check Description
			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		//Unit test for functionality of addDetails - Description - only whitespace in the description
		TEST_METHOD(testAddDetails_Description_whitespace){
			Task testTask;
			string testDescription = "  ";

			testTask.addDetails("  ; date 270315 to 290315; time 1300 to 1500");

			//Check Description
			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		//Unit test for functionality of addDetails - Description - blank with delimiter
		TEST_METHOD(testAddDetails_Description_blankDelimiter){
			Task testTask;
			string testDescription = "";

			testTask.addDetails("; date 270315 to 290315; time 1300 to 1500");

			//Check Description
			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		//Unit test for functionality of addDetails - Description - blank with no delimiter
		//maybe?
		TEST_METHOD(testAddDetails_Description_blank){
			Task testTask;
			string testDescription = "No description";

			testTask.addDetails("date 270315 to 290315; time 1300 to 1500");

			//Check Description
			Assert::AreEqual(testTask.getDescription(), testDescription);
		}

		/************************************************************

								Date Unit Tests

		************************************************************/

		//Unit test for functionality of addDetails - Date - start day
		TEST_METHOD(testAddDetails_Date_startDay){
			taskDate dateStartControl;
			Task testTask;

			dateStartControl.day = 15;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateStartControl.day, testTask.getDateStart().day);
		}

		//Unit test for functionality of addDetails - Date - start month
		TEST_METHOD(testAddDetails_Date_startMonth){
			taskDate dateStartControl;
			Task testTask;

			dateStartControl.month = 3;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateStartControl.month, testTask.getDateStart().month);
		}

		//Unit test for functionality of addDetails - Date - start year
		TEST_METHOD(testAddDetails_Date_startYear){
			taskDate dateStartControl;
			Task testTask;

			dateStartControl.year = 15;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateStartControl.year, testTask.getDateStart().year);
		}

		//Unit test for functionality of addDetails - Date - no start date
		TEST_METHOD(testAddDetails_Date_noStart){
			taskDate dateStartControl;
			Task testTask;
			bool isEmpty;

			testTask.addDetails("Meeting in school; date 150315; time 1300 to 1500");

			if (dateStartControl.year == -1 && dateStartControl.month == -1 && dateStartControl.day == -1){
				isEmpty = true;
			}

			Assert::IsTrue(isEmpty);
		}

		//Unit test for functionality of addDetails - Date - end day
		TEST_METHOD(testAddDetails_Date_EndDay){
			taskDate dateEndControl;
			Task testTask;

			dateEndControl.day = 16;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.day, testTask.getDateEnd().day);
		}

		//Unit test for functionality of addDetails - Date - End month
		TEST_METHOD(testAddDetails_Date_EndMonth){
			taskDate dateEndControl;
			Task testTask;

			dateEndControl.month = 4;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.month, testTask.getDateEnd().month);
		}

		//Unit test for functionality of addDetails - Date - End year
		TEST_METHOD(testAddDetails_Date_EndYear){
			taskDate dateEndControl;
			Task testTask;

			dateEndControl.year = 16;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.year, testTask.getDateEnd().year);
		}

			//boundary case for positive value partition: 3 digits in each date field
			//boundary case for positive value partition: 1 digit in each field;
			//Partition for negative dates
			//Partition for switch of start and end date

		/************************************************************

								Time Unit Tests

		************************************************************/

		TEST_METHOD(testAddDetails_Time){
			Task testTask1, testTask2, testTask3;
			bool isDescCorrect = false, isTimeCorrect = false;

			testTask1.addDetails("Meeting in school; date 270315 to 290315; time 1300 to 1500");

			Assert::AreNotEqual(3, testTask1.getNumOfTimes());
			Assert::AreEqual(2, testTask1.getNumOfTimes());

			if (testTask1.getTimeStart() == 1300 && testTask1.getTimeEnd() == 1500){
				isTimeCorrect = true;
			}
			Assert::IsTrue(isTimeCorrect);
		}

		TEST_METHOD(testIsSearchTargetPresent){
			Task testTask;
			string positiveSearchTarget = "meeting", negativeSearchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsTrue(testTask.isSearchTargetPresent(positiveSearchTarget));
			Assert::IsFalse(testTask.isSearchTargetPresent(negativeSearchTarget));

		}

	};
}