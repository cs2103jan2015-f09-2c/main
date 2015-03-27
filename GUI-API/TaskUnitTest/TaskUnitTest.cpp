#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskUnitTest
{		
	TEST_CLASS(TaskUnitTest)
	{
	public:
		
		TEST_METHOD(addDetailsTest){
			Task testTask1, testTask2, testTask3;
			bool isDescCorrect = false, isTimeCorrect = false;
		
			testTask1.addDetails("Meeting in school; date 270315 to 290315; time 1300 to 1500");
			testTask2.addDetails("Project meeting; date 280315; time 1400");
			testTask3.addDetails("Consultation with prof");

			//Check Description
			if (testTask1.getDescription() == "Meeting in school"){
				isDescCorrect = true;
			}
			Assert::IsTrue(isDescCorrect);
			
			//Check Time
			//Equivalence partition [0 .. 2] is the range that produces true
			//Check boundary case 0, 1, 2 and 3
			Assert::AreNotEqual(3, testTask1.getNumOfTimes());
			Assert::AreEqual(2, testTask1.getNumOfTimes());
			Assert::AreEqual(1, testTask2.getNumOfTimes());
			Assert::AreEqual(0, testTask3.getNumOfTimes());

			if (testTask1.getTimeStart() == 1300 && testTask1.getTimeEnd() == 1500){
				isTimeCorrect = true;
			}
			Assert::IsTrue(isTimeCorrect);

			//Check Date
			//Equivalence partition [0 .. 2] is the range that produces true
			//Check boundary case 0, 1, 2 and 3
			Assert::AreNotEqual(3, testTask1.getNumOfDates());
			Assert::AreEqual(2, testTask1.getNumOfDates());
			Assert::AreEqual(1, testTask2.getNumOfDates());
			Assert::AreEqual(0, testTask3.getNumOfDates());

		}

		TEST_METHOD(isSearchTargetPresentTest){
			Task testTask;
			string positiveSearchTarget = "meeting", negativeSearchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsTrue(testTask.isSearchTargetPresent(positiveSearchTarget));
			Assert::IsFalse(testTask.isSearchTargetPresent(negativeSearchTarget));

		}

		TEST_METHOD(storeDateTest){
			taskDate dateStartControl;
			taskDate dateEndControl;
			Task testTask;

			dateStartControl.day = 44;
			dateStartControl.month = 55;
			dateStartControl.year = 66;

			dateEndControl.day = 11;
			dateEndControl.month = 22;
			dateEndControl.year = 33;

			testTask.addDetails("Meeting in school; date 445566 to 112233; time 1300 to 1500");

			Assert::AreEqual(dateEndControl.day, testTask.getDateEnd().day);
			Assert::AreEqual(dateEndControl.month, testTask.getDateEnd().month);
			Assert::AreEqual(dateEndControl.year, testTask.getDateEnd().year);

			Assert::AreEqual(dateStartControl.day, testTask.getDateStart().day);
			Assert::AreEqual(dateStartControl.month, testTask.getDateStart().month);
			Assert::AreEqual(dateStartControl.year, testTask.getDateStart().year);


			//boundary case - 3 digits in each date field
			dateStartControl.day = 445;
			dateStartControl.month = 455;
			dateStartControl.year = 566;

			dateEndControl.day = 112;
			dateEndControl.month = 122;
			dateEndControl.year = 233;

			Assert::AreNotEqual(dateEndControl.day, testTask.getDateEnd().day);
			Assert::AreNotEqual(dateEndControl.month, testTask.getDateEnd().month);
			Assert::AreNotEqual(dateEndControl.year, testTask.getDateEnd().year);

			Assert::AreNotEqual(dateStartControl.day, testTask.getDateStart().day);
			Assert::AreNotEqual(dateStartControl.month, testTask.getDateStart().month);
			Assert::AreNotEqual(dateStartControl.year, testTask.getDateStart().year);

			//boundary case: 1 digit in each field;
			dateStartControl.day = 4;
			dateStartControl.month = 5;
			dateStartControl.year = 6;

			dateEndControl.day = 1;
			dateEndControl.month = 2;
			dateEndControl.year = 3;

			Assert::AreNotEqual(dateEndControl.day, testTask.getDateEnd().day);
			Assert::AreNotEqual(dateEndControl.month, testTask.getDateEnd().month);
			Assert::AreNotEqual(dateEndControl.year, testTask.getDateEnd().year);

			Assert::AreNotEqual(dateStartControl.day, testTask.getDateStart().day);
			Assert::AreNotEqual(dateStartControl.month, testTask.getDateStart().month);
			Assert::AreNotEqual(dateStartControl.year, testTask.getDateStart().year);
		}

	};
}