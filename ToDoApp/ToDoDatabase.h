#pragma once

#include "ToDoData.h"
#include <vector>
#include <iostream>
#include <fstream>

#define DEFAULTPATH "data/tododatabase.txt"
#define DEFAULTNAME "EmptyDatabase"

class ToDoDatabase
{
public:
	ToDoDatabase(void);
	ToDoDatabase(string path, string fileName);
	virtual ~ToDoDatabase(void);

	int getEntryCount() const;
	string getPath() const;
	void setPath(string path);
	void add(ToDoData * data);
	ToDoData * getEntryAt(int index) const;
	vector<ToDoData *> getAllEntries() const;
	void removeEntryAt(int index);
	void removeAllEntries();
	void removeAllUncheckedEntries();
	bool loadData();
	bool loadDataFrom(string path);
	bool loadDataFrom(fstream stream);
	bool saveData();
	bool saveDataTo(string path);

	string extractNameFromPath(string path);
	string getName() const;
	void setName(string name);
	static string getFileExtension(){
		return ".txt";
	}

private:
	vector<ToDoData *> m_dataVec;
	string m_path;
	string m_name;
};

