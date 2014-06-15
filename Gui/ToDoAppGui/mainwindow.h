#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>

#include <hash_map>
#include "C:\Program Files (x86)\Microsoft Visual Studio 11.0\VC\include\dirent.h"

#include "../../../ToDoApp/ToDoApp/ToDoDatabase.h"
#include <string>

#define DEFAULTDATAPATH "../data/"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool loadDatabases();
    bool loadConfiguration();
	void loadItems();
    void addCategory();
	void addItemForData(ToDoData * data);
    void changeActiveCategoryTo(int index);
	void removeChildrenOf(QLayout * layout);
	void saveItemsToCurDatabase();

	static QFrame * createItemFrom(ToDoData * data);
	static QFrame * createItem();
	static QFrame * createItem(string title, string description, bool done);



public slots:
	void onCategoryNameChanged(QString name);
	void onNextCategory();
	void onPrevCategory();

	void onSave();
	void onSaveAll();
	void onSaveTo();

	void onAddItem();

private:
    Ui::MainWindow *ui;
    vector<ToDoDatabase *> m_databases;
    int m_curDatabaseIndex;
    //hash_map<string, int> m_idDictionary;
};

#endif // MAINWINDOW_H
