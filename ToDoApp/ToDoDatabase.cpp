
#include "ToDoDatabase.h"


ToDoDatabase::ToDoDatabase(void)
{
	m_dataVec = vector<ToDoData *>();
	m_path = DEFAULTPATH;
	m_name = DEFAULTNAME;
}

ToDoDatabase::ToDoDatabase(string path, string fileName)
{
	m_dataVec = vector<ToDoData *>();
	m_path = path;
	m_name = extractNameFromPath(fileName);
	loadDataFrom(m_path);

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

string ToDoDatabase::getName()
{
	return m_name;
}

void ToDoDatabase::setName(string name)
{
	m_name = name;
}

string ToDoDatabase::extractNameFromPath(string path)
{
	vector<string> pathParts = ToDoDatabase::splitStringAt(path, '/');

	if(pathParts.size() > 0)
		return ToDoDatabase::splitStringAt(pathParts.back().c_str(), '.').begin()->c_str();

	return DEFAULTNAME;
}

vector<string> ToDoDatabase::splitStringAt(string sentence, char delim)
{
	vector<string> vec;

	stringstream sstream(sentence);
	string item;

	while(getline(sstream, item, delim))
		vec.push_back(item);

	return vec;
}


bool ToDoDatabase::loadData()
{
	return loadDataFrom(m_path + m_name + ".txt");
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

bool ToDoDatabase::loadDataFrom(fstream stream)
{
	string line;

	if(stream.is_open()){
		cout << "Reading from file at: " << stream << endl;

		while( getline(stream, line))
		{
			add(ToDoData::stringToData(line));
		}

		stream.close();
	}else{
		cout << "Unable to open file at: " << stream << endl;
		return false;
	}

	return true;
}

bool ToDoDatabase::saveData()
{
	return saveDataTo(m_path + m_name + ".txt");
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