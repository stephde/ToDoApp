#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void addCategory();
    void changeActiveCategoryTo(ToDoDatabase *tddb);

private:
    Ui::MainWindow *ui;
    vector<ToDoDatabase *> m_databases;
    ToDoDatabase * m_curDatabase;
    hash_map<string, int> m_idDictionary;
};

#endif // MAINWINDOW_H
