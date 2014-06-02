#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	m_curDatabase = NULL;
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

    DIR *dir = opendir(DEFAULTDATAPATH);
    dirent *d;
    ToDoDatabase * db;

    if(dir != NULL)
    {
        while((d = readdir(dir)) != NULL)
        {
			if( (string(d->d_name)).compare(".") && (string(d->d_name)).compare("..") )
				filesInDir->push_back(d->d_name);
		}
		
        for(int i=0; i< filesInDir->size(); i++)//vector<string>::iterator it; it != filesInDir->end(); it++)
        {
            db = new ToDoDatabase(DEFAULTDATAPATH + filesInDir->at(i));
			m_databases.push_back(db);
        }
    }else{
        return false;
    }

	changeActiveCategoryTo(m_databases.at(0));

    return true;
}


void MainWindow::changeActiveCategoryTo(ToDoDatabase *tddb)
{
	m_curDatabase = tddb;

	//load data into UI
	//ui->
	ui->lineEditCategory->setText(tddb->getName().c_str());
}
