#pragma once

#include <string>
#include <ctime>
#include <sstream>

using namespace std;

class ToDoData
{
public:
	ToDoData(void);
	ToDoData(string title, string description);	
	ToDoData(string title, string description, bool isDone);	
	ToDoData(string title, string description, time_t millis);
	ToDoData(string title, string description, bool isDone, time_t millis);
	virtual ~ToDoData(void);
	string getTitle();
	string getDescription();
	struct tm getCreationTime();
	time_t getCreationTimeMillis();
	bool isDone();
	void toggleIsDone();
	
	static ToDoData * stringToData(string str);
	static string dataToString(ToDoData * data);
	static bool stringToBool(string value);

private:
	string m_title;
	string m_description;
	time_t m_creationTime;
	bool m_isDone;
};

