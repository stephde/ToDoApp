
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
	loadData();

}

ToDoDatabase::~ToDoDatabase(void)
{

}

int ToDoDatabase::getEntryCount() const
{
	return m_dataVec.size();
}

void ToDoDatabase::add(ToDoData * data)
{
	m_dataVec.push_back(data);
}

ToDoData * ToDoDatabase::getEntryAt(int index) const
{
	return m_dataVec.at(index);
}

vector<ToDoData *> ToDoDatabase::getAllEntries() const
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

void ToDoDatabase::removeAllUncheckedEntries()
{
	for(int i=0; i<m_dataVec.size(); i++)
	{
		if(!m_dataVec.at(i)->isDone())
			m_dataVec.erase(m_dataVec.begin()+i);
	}
}

string ToDoDatabase::getPath() const
{
	return m_path;
}

void ToDoDatabase::setPath(string path)
{
	m_path = path;
}

string ToDoDatabase::getName() const
{
	return m_name;
}

void ToDoDatabase::setName(string name)
{
	m_name = name;
}

string ToDoDatabase::extractNameFromPath(string path)
{
	vector<string> pathParts = ToDoData::splitStringAt(path, '/');

	if(pathParts.size() > 0)
		return ToDoData::splitStringAt(pathParts.back().c_str(), '.').begin()->c_str();

	return DEFAULTNAME;
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
	return saveDataTo(m_path + m_name + ToDoDatabase::getFileExtension());
}

bool ToDoDatabase::saveDataTo(string path)
{
	string line;
	fstream file;
	file.open(path, fstream::out);

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