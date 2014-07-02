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

			Assert::AreEqual(0, d->getTitle().compare(string("Title")));
			Assert::AreEqual(0, d->getDescription().compare(string("Description")));
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
			
			Assert::AreEqual(0, d->getTitle().compare(string("Title")));
			Assert::AreEqual(0, d->getDescription().compare(string("Description")));
		}

		TEST_METHOD(TestDatabaseGetAll)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			tddb->add(new ToDoData("Title2", "Description2"));	
			vector<ToDoData *> d = tddb->getAllEntries();
			
			Assert::AreEqual(size_t(2), d.size());
		}

		TEST_METHOD(TestDatabaseRemove)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			tddb->removeEntryAt(0);
			
			Assert::AreEqual(0, tddb->getEntryCount());
		}

		TEST_METHOD(TestDatabaseRemoveAll)
		{			
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description"));		
			tddb->add(new ToDoData("Title2", "Description2"));		
			tddb->removeAllEntries();
			
			Assert::AreEqual(0, tddb->getEntryCount());
		}

		TEST_METHOD(TestRemoveAllUnchecked)
		{
			ToDoDatabase * tddb = new ToDoDatabase();
			tddb->add(new ToDoData("Title", "Description", true));
			tddb->add(new ToDoData("Title2", "Description2", true));
			tddb->add(new ToDoData("Title3", "Description3", false));

			tddb->removeAllUncheckedEntries();

			Assert::AreEqual(2, tddb->getEntryCount());
		}

		TEST_METHOD(TestStringToData)
		{			
			time_t t = time(NULL);
			string testStr = "title|description|0|" + to_string((int)t);
			ToDoData * data = ToDoData::stringToData(testStr);
			
			Assert::AreEqual(0, data->getTitle().compare("title"));			
			Assert::AreEqual(0, data->getDescription().compare("description"));
			Assert::AreEqual(false, data->isDone());
			Assert::AreEqual((int)t, (int)data->getCreationTimeMillis());
		}

		TEST_METHOD(TestStringToDataMultipleWords)
		{
			string testStr = "multiple words title" + ToDoData::getDelimiterString() 
							+ "multiple words description" + ToDoData::getDelimiterString() 
							+ "1" + ToDoData::getDelimiterString() + "1234";
			ToDoData * data = ToDoData::stringToData(testStr);

			
			Logger::WriteMessage(data->getTitle().c_str());
			Logger::WriteMessage(data->getDescription().c_str());

			Assert::AreEqual(0, data->getTitle().compare("multiple words title"));
			Assert::AreEqual(0, data->getDescription().compare("multiple words description"));
			Assert::AreEqual(true, data->isDone());
		}

		TEST_METHOD(TestDataToString)
		{			
			time_t t = time(NULL);
			ToDoData * data = new ToDoData("Title", "Description", t);
			string str = ToDoData::dataToString(data);

			Logger::WriteMessage(str.c_str());

			Assert::AreEqual(0, str.compare("Title|Description|false|" + to_string(t)));
		}
			
		TEST_METHOD(TestDefaultPath)
		{
			ToDoDatabase * tddb = new ToDoDatabase();

			Assert::AreEqual(0, tddb->getPath().compare("data/tododatabase.txt"));
		}

		TEST_METHOD(TestSetPath)
		{
			ToDoDatabase * tddb = new ToDoDatabase("data/test", "");

			Assert::AreEqual(0, tddb->getPath().compare("data/test"));
		}

		TEST_METHOD(TestLoadFromPath)
		{
			ToDoDatabase * tddb = new ToDoDatabase();			

			Assert::AreEqual(false, tddb->loadDataFrom("wrongPath..."));
		}

		TEST_METHOD(TestLoadFromFile)
		{
			ToDoDatabase * tddb = new ToDoDatabase();

			Assert::AreEqual(false, tddb->loadDataFrom(fstream()));
		}

		TEST_METHOD(TestSplitString)
		{
			string testString = "Das ist ein Test";

			Assert::AreEqual(0, ToDoData::splitStringAt(testString, ' ').back().compare("Test"));
		}

		TEST_METHOD(TestExtractNameFromPath)
		{
			ToDoDatabase * tddb = new ToDoDatabase();
			Assert::AreEqual(0, tddb->getName().compare(DEFAULTNAME));
			
			tddb = new ToDoDatabase("../aPath/", "aDatabaseName.txt");
			Assert::AreEqual(0, tddb->getName().compare("aDatabaseName"));
		}

	};
}