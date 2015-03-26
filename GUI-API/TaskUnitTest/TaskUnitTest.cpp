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
			bool isDescCorrect = false, isTimeCorrect = false, isStartDateCorrect = false, isEndDateCorrect = false;
		
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

			if (testTask1.getDateStart().day == 27 && testTask1.getDateStart().month == 3 && 
					testTask1.getDateStart().year == 15){
				isStartDateCorrect = true;
			}
			Assert::IsTrue(isStartDateCorrect);

			if (testTask1.getDateEnd().day == 29 && testTask1.getDateEnd().month == 3 && 
					testTask1.getDateEnd().year == 15){
				isEndDateCorrect = true;
			}
			Assert::IsTrue(isEndDateCorrect);


		}

		TEST_METHOD(isSearchTargetPresentTest){
			Task testTask;
			string positiveSearchTarget = "meeting", negativeSearchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsTrue(testTask.isSearchTargetPresent(positiveSearchTarget));
			Assert::IsFalse(testTask.isSearchTargetPresent(negativeSearchTarget));

		}

	};
}