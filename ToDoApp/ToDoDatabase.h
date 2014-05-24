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
	virtual ~ToDoDatabase(void);
	int getEntryCount();
	void add(ToDoData * data);
	ToDoData * getEntryAt(int index);
	vector<ToDoData *> getAllEntries();
	void removeEntryAt(int index);
	void removeAllEntries();
	void loadData();
	void loadDataFrom(char * path);


private:
	vector<ToDoData *> m_dataVec;
};

