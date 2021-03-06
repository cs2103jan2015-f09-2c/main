#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PlannerUnitTest
{
	TEST_CLASS(PlannerTest)
	{
	public:


		/************************************************************************************************

		"Add" Unit Tests

		************************************************************************************************/
		//@author A0111361Y
		TEST_METHOD(testAdd_oneTask)
		{
			Planner testPlanner;
			Task testTask;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n";
			testTask.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask);
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}
		//@author A0111361Y
		TEST_METHOD(testAdd_manyTasks)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 3 Time: 1900 \r\n2. Test task 1 Date: 1/2/3 Time: 1100 #impt\r\n3. Test task 2 Date: 11/3/15 to 12/3/15 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100 #impt"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			string actualOutput = testPlanner.AllToString();
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
		TEST_METHOD(testAdd_manyTasks_differentDates_noTime)
		{
			Planner testPlanner;
			string expectedOutput = "1. Test task 3 Date: 2/4/15 \r\n2. Test task 1 Date: 3/4/15 \r\n3. Test task 2 Date: 4/4/15 \r\n";
			Task testTask1, testTask2, testTask3;
			testTask1.addDetails("Test task 1, date 030415"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 040415");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 020415"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			string actualOutput = testPlanner.AllToString();
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
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

		/************************************************************************************************

		"Clear" Unit Test

		************************************************************************************************/

		//@author A0111361Y
		TEST_METHOD(testClear)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string testDisplayString, hardcodedDisplayString = "There are no tasks here\n";
			bool doesFunctionWork = false;
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.clear();
			testDisplayString = testPlanner.AllToString();

			Assert::AreEqual(hardcodedDisplayString, testDisplayString);
		}
		/************************************************************************************************

		"Delete" Unit Tests

		************************************************************************************************/

		//@author A0111361Y
		TEST_METHOD(testDelete_Missed_Delete_Task_1)
		{
			Planner testPlanner;
			string expectedOutput = "1. Test task 2 Date: 11/3/15 to 12/3/15 \r\n2. Test task 3 Date: 13/3/15 Time: 1900 \r\n";
			Task testTask1, testTask2, testTask3;
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.deleteTask(1, "Missed");
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
		TEST_METHOD(testDelete_Missed_Delete_Task_2)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n2. Test task 3 Date: 13/3/15 Time: 1900 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.deleteTask(2, "Missed");
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}
		/************************************************************************************************

		"Edit" Unit Tests

		************************************************************************************************/

		//@author A0111361Y
		TEST_METHOD(testEdit)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 EDITED Date: 1/2/3 Time: 1100 \r\n2. Test task 2 Date: 11/3/15 to 12/3/15 \r\n3. Test task 3 Date: 13/3/15 Time: 1900 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.editTask(1, "Missed", "Test task 1 EDITED, date 010203, time 1100");
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		/************************************************************************************************

		"Undo" Unit Tests

		************************************************************************************************/

		//@author A0111361Y
		TEST_METHOD(testUndo_Add)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n2. Test task 2 Date: 11/3/15 to 12/3/15 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.undo();
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
		TEST_METHOD(testUndo_Delete)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n2. Test task 2 Date: 11/3/15 to 12/3/15 \r\n3. Test task 3 Date: 13/3/15 Time: 1900 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.deleteTask(2, "Missed");
			testPlanner.undo();
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
		TEST_METHOD(testUndo_Edit)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n2. Test task 2 Date: 11/3/15 to 12/3/15 \r\n3. Test task 3 Date: 13/3/15 Time: 1900 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.editTask(1, "Missed", "Test task 1 EDITED; date 010203, time 1100");
			testPlanner.undo();
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		/************************************************************************************************

		"Load" Unit Tests

		************************************************************************************************/


		//@author A0111361Y
		TEST_METHOD(testLoad_Planner)
		{
			Planner testPlanner;
			string expectedOutput = "1. Test task 3 Time: 1900 \r\n2. Test task 1 Date: 1/2/3 Time: 1100 \r\n3. Test task 2 Date: 11/3/15 to 12/3/15 \r\n";
			string data;
			data = "Test task 1, date 010203, time 1100\nTest task 2, date 110315 to 120315\nTest task 3, time 1900\n";
			testPlanner.loadData(data);
			string actualOutput = testPlanner.AllToString();
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		/************************************************************************************************

		"Done" Unit Tests

		************************************************************************************************/


		//@author A0111361Y
		TEST_METHOD(testMark_Done_effect_on_missed_list_1_task)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n2. Test task 3 Date: 13/3/15 Time: 1900 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.markDone(2, "Missed");
			string actualOutput = testPlanner.toString("Missed");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
		TEST_METHOD(testMark_Done_effect_on_done_list_1_task)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 2 Date: 11/3/15 to 12/3/15 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, date 130315, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.markDone(2, "Missed");
			string actualOutput = testPlanner.toString("Done");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		//@author A0111361Y
		TEST_METHOD(testMark_Done_effect_on_done_list_2_task)
		{
			Planner testPlanner;
			Task testTask1, testTask2, testTask3;
			string expectedOutput = "1. Test task 1 Date: 1/2/3 Time: 1100 \r\n2. Test task 2 Date: 11/3/15 to 12/3/15 \r\n";
			testTask1.addDetails("Test task 1, date 010203, time 1100"); //assume Task.addDetail works
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 110315 to 120315");
			testPlanner.addTask(testTask2);
			testTask3.addDetails("Test task 3, time 1900"); //assume Task.addDetail works
			testPlanner.addTask(testTask3);
			testPlanner.markDone(2, "Missed");
			testPlanner.markDone(1, "Missed");
			string actualOutput = testPlanner.toString("Done");
			Assert::AreEqual(expectedOutput, actualOutput);
		}

		/************************************************************************************************

		"Clash" Unit Tests

		************************************************************************************************/

		//@author A0111314A
		TEST_METHOD(testClash_2date2time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			string finalOutput, hardcodedOutput;

			testTask1.addDetails("Test task 1, date 050415 to 070415, time 1100 to 1300");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 050415 to 070415, time 1000 to 1200");
			testPlanner.addTask(testTask2);
			finalOutput = testPlanner.toString("Missed");
			hardcodedOutput = "1. Test task 2 Date: 5/4/15 to 7/4/15 Time: 1000 to 1200  TASK CLASH !!!\r\n2. Test task 1 Date: 5/4/15 to 7/4/15 Time: 1100 to 1300  TASK CLASH !!!\r\n";

			Assert::AreEqual(hardcodedOutput, finalOutput);
		}

		//@author A0111314A
		TEST_METHOD(testClash_2date1time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			string finalOutput, hardcodedOutput;

			testTask1.addDetails("Test task 1, date 050415 to 070415, time 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 050415 to 070415, time 1200");
			testPlanner.addTask(testTask2);
			finalOutput = testPlanner.toString("Missed");
			hardcodedOutput = "1. Test task 1 Date: 5/4/15 to 7/4/15 Time: 1200  TASK CLASH !!!\r\n2. Test task 2 Date: 5/4/15 to 7/4/15 Time: 1200  TASK CLASH !!!\r\n";

			Assert::AreEqual(hardcodedOutput, finalOutput);
		}

		//@author A0111314A
		TEST_METHOD(testClash_1date1time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			string finalOutput, hardcodedOutput;

			testTask1.addDetails("Test task 1, date 070415, time 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 070415, time 1200");
			testPlanner.addTask(testTask2);
			finalOutput = testPlanner.toString("Missed");
			hardcodedOutput = "1. Test task 1 Date: 7/4/15 Time: 1200  TASK CLASH !!!\r\n2. Test task 2 Date: 7/4/15 Time: 1200  TASK CLASH !!!\r\n";

			Assert::AreEqual(hardcodedOutput, finalOutput);
		}

		//@author A0111314A
		TEST_METHOD(testClash_1date2time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;
			string finalOutput, hardcodedOutput;

			testTask1.addDetails("Test task 1, date 070415, time 1000 to 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 070415, time 1100 to 1300");
			testPlanner.addTask(testTask2);
			finalOutput = testPlanner.toString("Missed");
			hardcodedOutput = "1. Test task 1 Date: 7/4/15 Time: 1000 to 1200  TASK CLASH !!!\r\n2. Test task 2 Date: 7/4/15 Time: 1100 to 1300  TASK CLASH !!!\r\n";
			Assert::AreEqual(hardcodedOutput, finalOutput);
		}

		//@author A0111314A
		TEST_METHOD(testClash_12date1time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;
			string finalOutput, hardcodedOutput;

			testTask1.addDetails("Test task 1, date 060415, time 1200");
			testTask2.addDetails("Test task 2, date 050415 to 070415, time 1200");
			testPlanner.addTask(testTask1);
			testPlanner.addTask(testTask2);

			finalOutput = testPlanner.toString("Missed");
			hardcodedOutput = "1. Test task 2 Date: 5/4/15 to 7/4/15 Time: 1200  TASK CLASH !!!\r\n2. Test task 1 Date: 6/4/15 Time: 1200  TASK CLASH !!!\r\n";
			Assert::AreEqual(hardcodedOutput, finalOutput);
		}

		//@author A0111314A
		TEST_METHOD(testClash_12date2time) {
			Planner testPlanner;
			Task testTask1, testTask2;
			bool doesFunctionWork;
			string finalOutput, hardcodedOutput;

			testTask1.addDetails("Test task 1, date 060415, time 1000 to 1200");
			testPlanner.addTask(testTask1);
			testTask2.addDetails("Test task 2, date 050415 to 070415, time 1100 to 1300");
			testPlanner.addTask(testTask2);

			finalOutput = testPlanner.toString("Missed");
			hardcodedOutput = "1. Test task 2 Date: 5/4/15 to 7/4/15 Time: 1100 to 1300  TASK CLASH !!!\r\n2. Test task 1 Date: 6/4/15 Time: 1000 to 1200  TASK CLASH !!!\r\n";
			Assert::AreEqual(hardcodedOutput, finalOutput);

		}
	};
}