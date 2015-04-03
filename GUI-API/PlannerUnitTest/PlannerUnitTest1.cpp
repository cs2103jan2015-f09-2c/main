#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlannerUnitTest
{		
	TEST_CLASS(PlannerTest)
	{
	public:
		TEST_METHOD(testAdd_floating_Task)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			bool doesFunctionWork = false;
			testTask1.addDetails("Test task 1"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2"); 
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3"); 
			testPlanner.addTask(testTask3);
			string s;
				s = testPlanner.toString("Home");
			if (testPlanner.toString("Home") == "1. Test task 1 \r\n2. Test task 2 \r\n3. Test task 3 \r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClash_2date2time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;

			testTask1.addDetails("Test task 1; date 050415 to 070415; time 1100 to 1300"); 
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 050415 to 070415; time 1000 to 1200");
			testPlanner.addTask(testTask2);
			if (testPlanner.toString("Home") == "1. Test task 2 5/4/15 to 7/4/15 1000 to 1200 TASK CLASH!!!\r\n2. Test task 1 5/4/15 to 7/4/15 1100 to 1300 TASK CLASH!!!\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClash_2date1time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;

			testTask1.addDetails("Test task 1; date 050415 to 070415; time 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 050415 to 070415; time 1200");
			testPlanner.addTask(testTask2);
			if (testPlanner.toString("Home") == "1. Test task 1 5/4/15 to 7/4/15 1200 TASK CLASH!!!\r\n2. Test task 2 5/4/15 to 7/4/15 1200 TASK CLASH!!!\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClash_1date1time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;

			testTask1.addDetails("Test task 1; date 070415; time 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 070415; time 1200");
			testPlanner.addTask(testTask2);
			if (testPlanner.toString("Home") == "1. Test task 1 7/4/15 1200 TASK CLASH!!!\r\n2. Test task 2 7/4/15 1200 TASK CLASH!!!\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClash_1date2time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;

			testTask1.addDetails("Test task 1; date 070415; time 1000 to 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 070415; time 1100 to 1300");
			testPlanner.addTask(testTask2);
			if (testPlanner.toString("Home") == "1. Test task 1 7/4/15 1000 to 1200 TASK CLASH!!!\r\n2. Test task 2 7/4/15 1100 to 1300 TASK CLASH!!!\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClash_12date1time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;

			testTask1.addDetails("Test task 1; date 060415; time 1200");
			
			testTask2.addDetails("Test task 2; date 050415 to 070415; time 1200");
			testPlanner.addTask(testTask1);
			testPlanner.addTask(testTask2);
			if (testPlanner.toString("Home") == "1. Test task 2 5/4/15 to 7/4/15 1200 TASK CLASH!!!\r\n2. Test task 1 6/4/15 1200 TASK CLASH!!!\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testClash_12date2time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;

			testTask1.addDetails("Test task 1; date 060415; time 1000 to 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 050415 to 070415; time 1100 to 1300");
			testPlanner.addTask(testTask2);
			//									"1. Test task 2 5/4/15 to 7/4/15 1100 to 1300 \r\n2. Test task 1 6/4/15 1000 to 1200 \r\n"

			if (testPlanner.toString("Home") == "1. Test task 2 5/4/15 to 7/4/15 1100 to 1300 TASK CLASH!!!\r\n2. Test task 1 6/4/15 1000 to 1200 TASK CLASH!!!\r\n"){
				doesFunctionWork = true;
			}
			else{
				doesFunctionWork = false;
			}

			Assert::IsTrue(doesFunctionWork);
		}
		
		TEST_METHOD(testAdd_oneTask)
		{
			Planner testPlanner;
			Task testTask;
			bool doesFunctionWork=false;
			testTask.addDetails("Test task 1; date 010203; time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask);
			if (testPlanner.AllToString() == "1. Test task 1 1/2/3 1100 \r\n"){
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
			if (testPlanner.AllToString() == "1. Test task 3 1900 \r\n2. Test task 1 1/2/3 1100 \r\n3. Test task 2 11/3/15 to 12/3/15 \r\n"){
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
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.deleteTask(2, "Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100 \r\n2. Test task 3 13/3/15 1900 \r\n"){
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
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.deleteTask(1, "Missed");
			if (testPlanner.toString("Missed") == "1. Test task 2 11/3/15 to 12/3/15 \r\n2. Test task 3 13/3/15 1900 \r\n"){
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
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.editTask(1, "Missed", "Test task 1 EDITED; date 010203; time 1100");
			string s =testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 EDITED 1/2/3 1100 \r\n2. Test task 2 11/3/15 to 12/3/15 \r\n3. Test task 3 13/3/15 1900 \r\n"){
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
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100 \r\n2. Test task 2 11/3/15 to 12/3/15 \r\n"){
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
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.deleteTask(2, "Missed");
			testPlanner.undo();
			string s = testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100 \r\n2. Test task 2 11/3/15 to 12/3/15 \r\n3. Test task 3 13/3/15 1900 \r\n"){
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
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.editTask(1, "Missed", "Test task 1 EDITED; date 010203; time 1100");
			testPlanner.undo();
			string s = testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100 \r\n2. Test task 2 11/3/15 to 12/3/15 \r\n3. Test task 3 13/3/15 1900 \r\n"){
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
			data = testPlanner.AllToString();
			if (testPlanner.AllToString() == "1. Test task 3 1900 \r\n2. Test task 1 1/2/3 1100 \r\n3. Test task 2 11/3/15 to 12/3/15 \r\n"){                            
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
		}

		TEST_METHOD(testMark_Done_effect_on_missed_list_1_task)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			bool doesFunctionWork = false;
			testTask1.addDetails("Test task 1; date 010203; time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.markDone(2, "Missed");
			string s = testPlanner.toString("Missed");
			if (testPlanner.toString("Missed") == "1. Test task 1 1/2/3 1100 \r\n2. Test task 3 13/3/15 1900 \r\n"){
				doesFunctionWork = true;
		}
			Assert::IsTrue(doesFunctionWork);
		}
		TEST_METHOD(testMark_Done_effect_on_done_list_1_task)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			bool doesFunctionWork = false;
			testTask1.addDetails("Test task 1; date 010203; time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2; date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3; date 130315; time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.markDone(2, "Missed");
			if (testPlanner.toString("Done") == "1. Test task 2 11/3/15 to 12/3/15  DONE\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
		}
		TEST_METHOD(testMark_Done_effect_on_done_list_2_task)
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
			testPlanner.markDone(1, "Missed");
			if (testPlanner.toString("Done") == "1. Test task 1 1/2/3 1100  DONE\r\n2. Test task 2 11/3/15 to 12/3/15  DONE\r\n"){
				doesFunctionWork = true;
			}
			Assert::IsTrue(doesFunctionWork);
		}
	};
}