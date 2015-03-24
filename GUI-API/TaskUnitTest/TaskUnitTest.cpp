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
			bool isDescCorrect=false;
		
			taskTwoDatesTwoTimes.addDetails("Meeting in school");
			
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


		}

	};
}