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


string ToDoData::getTitle() const
{	
	return m_title;
}

string ToDoData::getDescription() const
{
	return m_description;
}

struct tm ToDoData::getCreationTime() const
{
	struct tm tInfo;
	localtime_s(&tInfo, &m_creationTime);
	return tInfo;
}

time_t ToDoData::getCreationTimeMillis() const
{
	return m_creationTime;
}

bool ToDoData::isDone() const
{
	return m_isDone;
}

void ToDoData::toggleIsDone()
{
	m_isDone = !m_isDone;
}


vector<string> ToDoData::splitStringAt(string sentence, const char delim)
{
	vector<string> vec;

	stringstream sstream(sentence);
	string item;

	while(getline(sstream, item, delim))
		vec.push_back(item);

	return vec;
}

ToDoData * ToDoData::stringToData(const string str)
{
	string title = "", description = "", isDone = "", millis = "", tmp = "";
	vector<string> vec = ToDoData::splitStringAt(str, ToDoData::getDelimiter());

	if(vec.size() == 4)
	{
		title = vec.at(0);
		description = vec.at(1);
		isDone = vec.at(2);
		millis = vec.at(3);
	}

	return new ToDoData(title, description, ToDoData::stringToBool(isDone), time_t(atoi(millis.c_str())));
}

inline const string const BoolToString(bool b)
{
	return string(b ? "true" : "false");
}

string ToDoData::dataToString(ToDoData * data)
{
	string str = "";
	str.append(data->getTitle() + ToDoData::getDelimiter());
	str.append(data->getDescription() + ToDoData::getDelimiter());
	str.append(BoolToString(data->isDone()) + ToDoData::getDelimiter());
	str.append(to_string(data->getCreationTimeMillis()));
	return str;
}

bool ToDoData::stringToBool(string value)
{
	if(value == "0" || value == "false" || value == "FALSE" || value == "False")
		return false;
	else if(value == "1" || value == "true" || value == "TRUE" || value == "True")
		return true;
	else{
		//throw(new std::exception("Unsupported type encountered while parsing string to boolean!"));
		cout << "Unsupported type encountered while parsing string to boolean!";
		return false;
	}
}