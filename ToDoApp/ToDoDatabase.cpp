#include "stdafx.h"
#include "ToDoDatabase.h"


ToDoDatabase::ToDoDatabase(void)
{
	m_dataVec = vector<ToDoData *>();
	m_path = DEFAULTPATH;
}

ToDoDatabase::ToDoDatabase(string path)
{
	m_dataVec = vector<ToDoData *>();
	m_path = path;
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

string ToDoDatabase::getPath()
{
	return m_path;
}

void ToDoDatabase::setPath(string path)
{
	m_path = path;
}


bool ToDoDatabase::loadData()
{
	return loadDataFrom(m_path);
}

bool ToDoDatabase::loadDataFrom(string path)
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
	}else{
		cout << "Unable to open file at: " << path << endl;
		return false;
	}

	return true;
}

bool ToDoDatabase::saveData()
{
	return saveDataTo(DEFAULTPATH);
}

bool ToDoDatabase::saveDataTo(string path)
{
	string line;
	fstream file;
	file.open(path, ios::app);

	if(file.is_open()){
		cout << "Saving to file at: " << path << endl;

		for(vector<ToDoData *>::iterator it = m_dataVec.begin(); it != m_dataVec.end(); ++it)
		{
			file << ToDoData::dataToString(*it) << endl;
		}

		file.close();
	}else{
		cout << "Unable to open file at: " << path << endl;
		return false;
	}

	return true;
}