#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TaskUnitTest
{		
	TEST_CLASS(TaskUnitTest)
	{
	public:
		
		TEST_METHOD(addDetailsTest){
			Task taskTwoDatesTwoTimes, taskNoDateNoTime, taskOneDateOneTime, taskOneDateNoTime, taskNoDateTwoTimes;
			bool isDescCorrect = false, isTimeCorrect = false, isStartDateCorrect = false, isEndDateCorrect = false;
		
			taskTwoDatesTwoTimes.addDetails("Meeting in school; date 270315 to 290315; time 1300 to 1500");
			
			/*
			taskNoDateNoTime.addDetails("add Do CS Assignment");
			taskOneDateOneTime.addDetails("Meeting with Prof; date 270315; time 1400");
			taskOneDateNoTime.addDetails("Math Assignment; date 010415");
			taskNoDateTwoTimes.addDetails("Meet girlfriend for dinner; 1800 to 2030");
			*/

			//Check Description
			if (taskTwoDatesTwoTimes.getDescription() == "Meeting in school"){
				isDescCorrect = true;
			}
			Assert::IsTrue(isDescCorrect);
			
			//Check Time
			if (taskTwoDatesTwoTimes.getTimeStart() == 1300 && taskTwoDatesTwoTimes.getTimeEnd() == 1500){
				isTimeCorrect = true;
			}
			Assert::IsTrue(isTimeCorrect);

			//Check Date
			if (taskTwoDatesTwoTimes.getDateStart().day == 27 && taskTwoDatesTwoTimes.getDateStart().month == 3 && 
					taskTwoDatesTwoTimes.getDateStart().year == 15){
				isStartDateCorrect = true;
			}
			Assert::IsTrue(isStartDateCorrect);

			if (taskTwoDatesTwoTimes.getDateEnd().day == 29 && taskTwoDatesTwoTimes.getDateEnd().month == 3 && 
					taskTwoDatesTwoTimes.getDateEnd().year == 15){
				isEndDateCorrect = true;
			}
			Assert::IsTrue(isEndDateCorrect);


		}

		TEST_METHOD(isSearchTargetPresentTest){
			Task testTask;
			string positiveSearchTarget = "Meeting", negativeSearchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsTrue(testTask.isSearchTargetPresent(positiveSearchTarget));
			Assert::IsFalse(testTask.isSearchTargetPresent(negativeSearchTarget));

		}

	};
}