#include "stdafx.h"
#include "CppUnitTest.h"

#include "../ToDoApp/ToDoData.cpp"
#include "../ToDoApp/ToDoDatabase.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		//Test Data
		TEST_METHOD(TestConstructToDoData)
		{
			ToDoData * d = new ToDoData("Title", "Description");

			Assert::AreEqual(d->getTitle().compare(string("Title")), 0);
			Assert::AreEqual(d->getDescription().compare(string("Description")), 0);
		};

		TEST_METHOD(TestToDoDataConstructionDate)
		{
			time_t t;
			time(&t);

			struct tm tInfo;
			localtime_s(&tInfo, &t);
			
			ToDoData * d = new ToDoData();
			struct tm dataTime = d->getCreationTime();
	
			Assert::AreEqual(tInfo.tm_year, dataTime.tm_year);
			Assert::AreEqual(tInfo.tm_yday, dataTime.tm_yday);
			Assert::AreEqual(tInfo.tm_hour, dataTime.tm_hour);
		}

		//Test Database
		TEST_METHOD(TestDatabaseCount)
		{
			ToDoDatabase * tddb = new ToDoDatabase();

			Assert::AreEqual(0, tddb->getEntryCount());
			tddb->add(new ToDoData());			
			Assert::AreEqual(1, tddb->getEntryCount());
		}

		TEST_METHOD(TestDatabaseAddGet)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			ToDoData * d = tddb->getEntryAt(0);
			
			Assert::AreEqual(d->getTitle().compare(string("Title")), 0);
			Assert::AreEqual(d->getDescription().compare(string("Description")), 0);
		}

		TEST_METHOD(TestDatabaseGetAll)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			tddb->add(new ToDoData("Title2", "Description2"));	
			vector<ToDoData *> d = tddb->getAllEntries();
			
			Assert::AreEqual(d.size(), size_t(2));
		}

		TEST_METHOD(TestDatabaseRemove)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			tddb->removeEntryAt(0);
			
			Assert::AreEqual(tddb->getEntryCount(), 0);
		}

		TEST_METHOD(TestDatabaseRemoveAll)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			tddb->add(new ToDoData("Title2", "Description2"));		
			tddb->removeAllEntries();
			
			Assert::AreEqual(tddb->getEntryCount(), 0);
		}

		TEST_METHOD(TestStringToData)
		{			
			time_t t = time(NULL);
			string testStr = "title description " + to_string((int)t);
			ToDoData * data = ToDoData::stringToData(testStr);
			
			Assert::AreEqual(data->getTitle().compare("title"), 0);			
			Assert::AreEqual(data->getDescription().compare("title"), 0);
			Assert::AreEqual((int)data->getCreationTimeMillis(), (int)t);
		}
	};
}