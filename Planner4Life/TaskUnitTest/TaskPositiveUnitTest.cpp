#include "stdafx.h"
#include "CppUnitTest.h"
#include <list>

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
			string testControlDescription = "Meeting in school", testDescription;

			testTask.addDetails("Meeting in school; date 270315 to 290315; time 1300 to 1500");
			testDescription = testTask.getDescription();

			Assert::AreEqual(testControlDescription, testDescription);
		}

		TEST_METHOD(testAddDetails_Description_whitespace){
			Task testTask;
			string testControlDescription = "  ", testDescription;

			testTask.addDetails("  ; date 270315 to 290315; time 1300 to 1500");
			testDescription = testTask.getDescription();

			Assert::AreEqual(testControlDescription, testDescription);
		}

		TEST_METHOD(testAddDetails_Description_blankDelimiter){
			Task testTask;
			string testControlDescription = "", testDescription;

			testTask.addDetails("; date 270315 to 290315; time 1300 to 1500");
			testDescription = testTask.getDescription();

			Assert::AreEqual(testControlDescription, testDescription);
		}

		/************************************************************************************************

		Date Unit Tests

		************************************************************************************************/

		TEST_METHOD(testStoreStartDate_Date_startDay){
			taskDate dateStartControl;
			Task testTask;
			int testTaskDay;

			dateStartControl.day = 15;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");
			testTaskDay = testTask.getDateStart().day;

			Assert::AreEqual(dateStartControl.day, testTaskDay);
		}

		TEST_METHOD(testStoreStartDate_Date_startMonth){
			taskDate dateStartControl;
			Task testTask;
			int testTaskMonth;

			dateStartControl.month = 3;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");
			testTaskMonth = testTask.getDateStart().month;

			Assert::AreEqual(dateStartControl.month, testTaskMonth);
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

		TEST_METHOD(testProcessTime_twoTime_timeStart){
			Task testTask;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(1300, testTask.getTimeStart());
		}

		TEST_METHOD(testProcessTime_twoTime_timeEnd){
			Task testTask;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300 to 1500");

			Assert::AreEqual(1500, testTask.getTimeEnd());
		}

		TEST_METHOD(testProcessTime_oneTime_timeStart){
			Task testTask;
			int testTimeStart;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300");
			testTimeStart = testTask.getTimeStart();

			Assert::AreEqual(1300, testTimeStart);
		}

		TEST_METHOD(testProcessTime_oneTime_timeEnd){
			Task testTask;
			int testTimeEnd;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300");
			testTimeEnd = testTask.getTimeEnd();

			Assert::AreEqual(-1, testTimeEnd);
		}


		TEST_METHOD(testProcessTime_noTime_timeStart){
			Task testTask;
			int testTimeStart;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300");
			testTimeStart = testTask.getTimeStart();

			Assert::AreEqual(1300, testTimeStart);
		}


		TEST_METHOD(testProcessTime_noTime_timeEnd){
			Task testTask;
			int testTimeEnd;

			testTask.addDetails("Meeting in school; date 150315 to 160416; time 1300");
			testTimeEnd = testTask.getTimeEnd();

			Assert::AreEqual(-1, testTimeEnd);
		}

		/************************************************************************************************

		Search Unit Tests

		************************************************************************************************/

		//@author karthik
		TEST_METHOD(testSearchTarget_targetPresent){
			Task testTask;
			string searchTarget = "meeting";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsTrue(testTask.isSearchTargetPresent(searchTarget));
		}

		TEST_METHOD(testSearchTarget_targetNotPresent){
			Task testTask;
			string searchTarget = "class";

			testTask.addDetails("Meeting with Prof; date 270315; time 1400");

			Assert::IsFalse(testTask.isSearchTargetPresent(searchTarget));
		}

		/************************************************************************************************

		Recur Unit Tests

		************************************************************************************************/
		TEST_METHOD(testRecurTask_numOfTimesRecurred){
			Task testTask;
			int numOfTimesRecurred;

			testTask.recurTask("daily 5; Project meeting; date 250415; time 1500");
			numOfTimesRecurred = testTask.getRecurringTasks().size();

			Assert::AreEqual(5, numOfTimesRecurred);
		}

		//To test if the recurring tasks dates are updated. Recurring 5 times is chosen arbitrarily.
		//Date is specifically chosen to spill from one month to another for daily, one month to another for weekly, 
		//one year to another for monthly, to test the date changing logic
		//***** Daily Tests ******//
		TEST_METHOD(testRecurTask_Daily_RecurredFiveTimes_Date_Day){ 
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskDay;
			list<Task> taskList;

			testTask.recurTask("daily 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskDay = (*taskIter).getDateEnd().day;
			Assert::AreEqual(2, fifthRecurredTaskDay);
		}

		TEST_METHOD(testRecurTask_Daily_RecurredFiveTimes_Date_Month){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskMonth;
			list<Task> taskList;

			testTask.recurTask("daily 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskMonth = (*taskIter).getDateEnd().month;
			Assert::AreEqual(12, fifthRecurredTaskMonth);
		}
		
		TEST_METHOD(testRecurTask_Daily_RecurredFiveTimes_Date_Year){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskYear;
			list<Task> taskList;

			testTask.recurTask("daily 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskYear = (*taskIter).getDateEnd().year;
			Assert::AreEqual(15, fifthRecurredTaskYear);
		}

		//***** Monthly Tests ******//
		TEST_METHOD(testRecurTask_Monthly_RecurredFiveTimes_Date_Day){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskDay;
			list<Task> taskList;

			testTask.recurTask("monthly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskDay = (*taskIter).getDateEnd().day;
			Assert::AreEqual(28, fifthRecurredTaskDay);
		}

		TEST_METHOD(testRecurTask_Monthly_RecurredFiveTimes_Date_Month){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskMonth;
			list<Task> taskList;

			testTask.recurTask("monthly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskMonth = (*taskIter).getDateEnd().month;
			Assert::AreEqual(3, fifthRecurredTaskMonth);
		}

		TEST_METHOD(testRecurTask_Monthly_RecurredFiveTimes_Date_Year){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskYear;
			list<Task> taskList;

			testTask.recurTask("monthly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskYear = (*taskIter).getDateEnd().year;
			Assert::AreEqual(16, fifthRecurredTaskYear);
		}

		//***** Weekly Tests ******//
		TEST_METHOD(testRecurTask_Weekly_RecurredFiveTimes_Date_Day){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskDay;
			list<Task> taskList;

			testTask.recurTask("weekly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskDay = (*taskIter).getDateEnd().day;
			Assert::AreEqual(26, fifthRecurredTaskDay);
		}

		TEST_METHOD(testRecurTask_Weekly_RecurredFiveTimes_Date_Month){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskMonth;
			list<Task> taskList;

			testTask.recurTask("weekly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskMonth = (*taskIter).getDateEnd().month;
			Assert::AreEqual(12, fifthRecurredTaskMonth);
		}

		TEST_METHOD(testRecurTask_Weekly_RecurredFiveTimes_Date_Year){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskYear;
			list<Task> taskList;

			testTask.recurTask("weekly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskYear = (*taskIter).getDateEnd().year;
			Assert::AreEqual(15, fifthRecurredTaskYear);
		}

		//***** Yearly Tests ******//
		TEST_METHOD(testRecurTask_Yearly_RecurredFiveTimes_Date_Day){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskDay;
			list<Task> taskList;

			testTask.recurTask("yearly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskDay = (*taskIter).getDateEnd().day;
			Assert::AreEqual(28, fifthRecurredTaskDay);
		}

		TEST_METHOD(testRecurTask_Yearly_RecurredFiveTimes_Date_Month){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskMonth;
			list<Task> taskList;

			testTask.recurTask("yearly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskMonth = (*taskIter).getDateEnd().month;
			Assert::AreEqual(11, fifthRecurredTaskMonth);
		}

		TEST_METHOD(testRecurTask_Yearly_RecurredFiveTimes_Date_Year){
			Task testTask;
			taskDate updatedDateOfLastEntry;
			int fifthRecurredTaskYear;
			list<Task> taskList;

			testTask.recurTask("yearly 5; Project meeting; date 281115; time 1500");
			list<Task>::iterator taskIter;
			taskList = testTask.getRecurringTasks();
			taskIter = taskList.end();
			taskIter--;
			fifthRecurredTaskYear = (*taskIter).getDateEnd().year;
			Assert::AreEqual(19, fifthRecurredTaskYear);
		}

	};
}
