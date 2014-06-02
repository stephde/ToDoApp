#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    if(!loadDatabases())
        //alert could not load
        ;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/****
 *
 *  Auf bestimme dateiendung einschränken!!!
 *
 ***/

bool MainWindow::loadDatabases()
{
    vector<string> * filesInDir = new vector<string>;;

    DIR *dir = opendir("../../../data/");
    dirent *d;
    ToDoDatabase * db;

    if(dir != NULL)
    {
        while((d = readdir(dir)) != NULL)
        filesInDir->push_back(d->d_name);

        for(int i=0; i< filesInDir->size(); i++)//vector<string>::iterator it; it != filesInDir->end(); it++)
        {
            db = new ToDoDatabase();
            m_databases.push_back(db);
        }
    }else{
        return false;
    }

    return true;
}
