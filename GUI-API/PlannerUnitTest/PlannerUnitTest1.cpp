#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlannerUnitTest
{		
	TEST_CLASS(PlannerTest)
	{
	public:
		
		TEST_METHOD(TestAddFunction_1_task_only)
		{
			Planner testPlanner;
			Task testTask;
			bool doesFunctionWork=false;
			testTask.addDetails("Test task 1; date 010203; time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask);
			if (testPlanner.AllToString() == "1. Test task 1 1/2/3 1100\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}
		TEST_METHOD(TestAddFunction_multiple_tasks)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			bool doesFunctionWork = false;
			testTask1.addDetails("Test task 1; date 010203; time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 110315 to 120315"); 
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			if (testPlanner.AllToString() == "1. Test task 1 1/2/3 1100\r\n2. Test task 3 1900\r\n3. Test task 2 11/3/15 to 12/3/15 \r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}
		TEST_METHOD(TestClearFunction)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			bool doesFunctionWork = false;
			testTask1.addDetails("Test task 1; date 010203; time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.clear();
			string s = testPlanner.AllToString();
			if (testPlanner.AllToString() == "The list is empty!\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}
	};
}