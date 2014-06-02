#include "ToDoData.h"


using namespace std;

ToDoData::ToDoData(void)
{
	m_creationTime = time(NULL);
}

ToDoData::ToDoData(string title, string description)
{
	m_creationTime = time(NULL);
	m_title = title;
	m_description = description;
}


ToDoData::ToDoData(string title, string description, time_t millis)
{
	m_creationTime = millis;
	m_title = title;
	m_description = description;
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

ToDoData * ToDoData::stringToData(string str)
{
	string title, description, millis;

	istringstream iss(str);
	iss >> title;
	iss >> description;
	iss >> millis;

	return new ToDoData(title, description, time_t(atoi(millis.c_str())));
}

string ToDoData::dataToString(ToDoData * data)
{
	string str = "";
	str.append(data->getTitle() + " ");
	str.append(data->getDescription() + " ");
	str.append(to_string(data->getCreationTimeMillis()));
	return str;
}