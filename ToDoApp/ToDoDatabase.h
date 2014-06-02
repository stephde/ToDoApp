#pragma once

#include "ToDoData.h"
#include <vector>
#include <iostream>
#include <fstream>

#define DEFAULTPATH "data/tododatabase.txt"

class ToDoDatabase
{
public:
	ToDoDatabase(void);
	ToDoDatabase(string path);
	virtual ~ToDoDatabase(void);

	int getEntryCount();
	string getPath();
	void setPath(string path);
	void add(ToDoData * data);
	ToDoData * getEntryAt(int index);
	vector<ToDoData *> getAllEntries();
	void removeEntryAt(int index);
	void removeAllEntries();
	bool loadData();
	bool loadDataFrom(string path);
	bool loadDataFrom(fstream stream);
	bool saveData();
	bool saveDataTo(string path);


private:
	vector<ToDoData *> m_dataVec;
	string m_path;
};

