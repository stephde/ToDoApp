#include "stdafx.h"
#include "ToDoDatabase.h"


ToDoDatabase::ToDoDatabase(void)
{
	m_dataVec = vector<ToDoData *>();
}


ToDoDatabase::~ToDoDatabase(void)
{

}

int ToDoDatabase::getEntryCount(){
	return m_dataVec.size();
}

void ToDoDatabase::add(ToDoData * data){
	m_dataVec.push_back(data);
}

ToDoData * ToDoDatabase::getEntryAt(int index)
{
	return m_dataVec.at(index);
}

vector<ToDoData *> ToDoDatabase::getAllEntries()
{
	return m_dataVec;
}

void ToDoDatabase::removeEntryAt(int index)
{
	m_dataVec.erase(m_dataVec.begin()+index);
}

void ToDoDatabase::removeAllEntries()
{
	m_dataVec.clear();
}


void ToDoDatabase::loadData()
{
	loadDataFrom(DEFAULTPATH);
}

void ToDoDatabase::loadDataFrom(char * path)
{
	string line;
	ifstream file;
	file.open(path);

	if(file.is_open()){
		cout << "Reading from file at: " << path << endl;

		while( getline(file, line))
		{
			add(ToDoData::stringToData(line));
		}

		file.close();
	}else
		cout << "Unable to open file at: " << path << endl;
}