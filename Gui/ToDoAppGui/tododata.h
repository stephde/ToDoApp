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
    ToDoData(string title, string description, time_t millis);
    virtual ~ToDoData(void);
    string getTitle();
    string getDescription();
    struct tm getCreationTime();
    time_t getCreationTimeMillis();

    static ToDoData * stringToData(string str);
    static string dataToString(ToDoData * data);

private:
    string m_title;
    string m_description;
    time_t m_creationTime;
};

