#pragma once

#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>

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
	
	string getTitle() const;
	string getDescription() const;
	struct tm getCreationTime() const;
	time_t getCreationTimeMillis() const;
	bool isDone() const;
	void toggleIsDone();
	
	static char getDelimiter(){
		return '|';
	}
	static string getDelimiterString(){
		return "|";
	}
	
	static vector<string> splitStringAt(string sentence, const char delim);
	static ToDoData * stringToData(const string str);
	static string dataToString(ToDoData * data);
	static bool stringToBool(string value);

private:
	string m_title;
	string m_description;
	time_t m_creationTime;
	bool m_isDone;
};

