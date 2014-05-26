// ToDoApp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "ToDoDatabase.h"


int main(int argc, char* argv[])
{
	ToDoDatabase * db = new ToDoDatabase();

	
	time_t t = time(NULL);
	string testStr = "title description " + to_string((int)t);
	ToDoData * data = ToDoData::stringToData(testStr);

	cout << data->getTitle().compare("title");

	return 0;
}

