#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlannerUnitTest
{		
	TEST_CLASS(PlannerTest)
	{
	public:
		
		TEST_METHOD(testAdd_oneTask)
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
		TEST_METHOD(testAdd_manyTasks)
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
			string s = testPlanner.AllToString();
			string t = testPlanner.toString("Missed");
			if (testPlanner.AllToString() == "1. Test task 1 1/2/3 1100\r\n2. Test task 2 11/3/15 to 12/3/15\r\n3. Test task 3 1900\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClear)
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
			if (testPlanner.AllToString() == "The list is empty\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testDelete_Missed_Delete_Task_2)
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
			testPlanner.deleteTask(2, "Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100\r\n2. Test task 3 1900\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
		}
		TEST_METHOD(testDelete_Missed_Delete_Task_1)
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
			testPlanner.deleteTask(1, "Missed");
			string s = testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 2 11/3/15 to 12/3/15\r\n2. Test task 3 1900\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
		}
		TEST_METHOD(testEdit)
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
			testPlanner.editTask(1, "Missed", "Test task 1 EDITED; date 010203; time 1100");
			string s =testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 EDITED 1/2/3 1100\r\n2. Test task 2 11/3/15 to 12/3/15\r\n3. Test task 3 1900\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);

		}

		TEST_METHOD(testUndo_Add)
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
			testPlanner.undo();
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100\r\n2. Test task 2 11/3/15 to 12/3/15\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);

		}

		TEST_METHOD(testUndo_Delete)
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
			testPlanner.deleteTask(2, "Missed");
			testPlanner.undo();
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100\r\n2. Test task 3 1900\r\n3. Test task 2 11/3/15 to 12/3/15\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
			
		}

		TEST_METHOD(testUndo_Edit)
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
			testPlanner.editTask(1, "Missed", "Test task 1 EDITED; date 010203; time 1100");
			testPlanner.undo();
			string s = testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100\r\n2. Test task 2 11/3/15 to 12/3/15\r\n3. Test task 3 1900\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);

		}

		TEST_METHOD(testLoad_Planner)
		{
			Planner testPlanner;
			bool doesFunctionWork = false;
			string data;
			data = "Test task 1; date 010203; time 1100\nTest task 2; date 110315 to 120315\nTest task 3; time 1900\n";
			testPlanner.loadData(data);
			if (testPlanner.AllToString() == "1. Test task 1 1/2/3 1100\r\n2. Test task 2 11/3/15 to 12/3/15\r\n3. Test task 3 1900\r\n"){
				                             

				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testMark_Done)
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
			testPlanner.markDone(2, "Missed");
			string s = testPlanner.toString("Missed");
		if (testPlanner.toString("Missed") == "Test task 1; date 010203; time 1100"){
		doesFunctionWork = true;
		}
			Assert::IsTrue(doesFunctionWork);
		}
	};
}