#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>

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
	void addItemForData(ToDoData * data);
    void changeActiveCategoryTo(int index);
	void removeChildrenOf(QLayout * layout);
	void saveItemsToCurDatabase();
	int getCategoryIndexForName(string name);

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

	void onAddCategory();
	void onChooseCategory();
	void onHideChooseCategory();
	void onCategoryChoosen();

	void onShowChecked(bool checked);

	void onAddItem();

private:
    Ui::MainWindow *ui;
    vector<ToDoDatabase *> m_databases;
    int m_curDatabaseIndex;
	bool m_showCheckedItems;
};

#endif // MAINWINDOW_H
