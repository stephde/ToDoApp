#include "ToDoData.h"


using namespace std;

ToDoData::ToDoData(void)
{
	m_creationTime = time(NULL);
	m_isDone = false;
}

ToDoData::ToDoData(string title, string description)
{
	m_creationTime = time(NULL);
	m_title = title;
	m_description = description;
	m_isDone = false;
}

ToDoData::ToDoData(string title, string description, bool isDone)
{
	m_creationTime = time(NULL);
	m_title = title;
	m_description = description;
	m_isDone = isDone;
}

ToDoData::ToDoData(string title, string description, time_t millis)
{
	m_creationTime = millis;
	m_title = title;
	m_description = description;
	m_isDone = false;
}

ToDoData::ToDoData(string title, string description, bool isDone, time_t millis)
{
	m_creationTime = millis;
	m_title = title;
	m_description = description;
	m_isDone = isDone;
}

ToDoData::~ToDoData(void)
{

}


string ToDoData::getTitle(){
	
	return m_title;
}

string ToDoData::getDescription(){

	return m_description;
}

struct tm ToDoData::getCreationTime(){
	struct tm tInfo;
	localtime_s(&tInfo, &m_creationTime);
	return tInfo;
}

time_t ToDoData::getCreationTimeMillis(){
	return m_creationTime;
}

bool ToDoData::isDone()
{
	return m_isDone;
}

void ToDoData::toggleIsDone()
{
	m_isDone = !m_isDone;
}


ToDoData * ToDoData::stringToData(string str)
{
	string title, description, isDone, millis;

	istringstream iss(str);
	iss >> title;
	iss >> description;
	iss >> isDone;
	iss >> millis;

	return new ToDoData(title, description, ToDoData::stringToBool(isDone), time_t(atoi(millis.c_str())));
}

string ToDoData::dataToString(ToDoData * data)
{
	string str = "";
	str.append(data->getTitle() + " ");
	str.append(data->getDescription() + " ");
	str.append((int)data->isDone() + " ");
	str.append(to_string(data->getCreationTimeMillis()));
	return str;
}

bool ToDoData::stringToBool(string value)
{
	if(value == "0" || value == "false" || value == "FALSE")
		return false;
	else if(value == "1" || value == "true" || value == "TRUE")
		return true;
	else
		throw(new std::exception("Unsupported type encountered while parsing string to boolean!"));
}