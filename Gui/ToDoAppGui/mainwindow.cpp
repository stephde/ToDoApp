#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	m_curDatabaseIndex = 0;
    ui->setupUi(this);

    if(!loadDatabases())
        //alert could not load
        ;

	QObject::connect(ui->lineEditCategory, SIGNAL(textChanged(QString)), this, SLOT(onCategoryNameChanged(QString)));
	QObject::connect(ui->buttonNext, SIGNAL(clicked()), this, SLOT(onNextCategory()));
	QObject::connect(ui->buttonPrevious, SIGNAL(clicked()), this, SLOT(onPrevCategory()));
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
            db = new ToDoDatabase(DEFAULTDATAPATH, filesInDir->at(i));
			m_databases.push_back(db);
        }
    }else{
        return false;
    }

	changeActiveCategoryTo(0);

    return true;
}


void MainWindow::changeActiveCategoryTo(int index)
{
	m_curDatabaseIndex = index;

	//load data into UI
	ui->lineEditCategory->setText(m_databases.at(index)->getName().c_str());
	//loadITems
}


void MainWindow::onCategoryNameChanged(QString name)
{
	m_databases.at(m_curDatabaseIndex)->setName(name.toStdString());
}

void MainWindow::onNextCategory()
{
	if(m_curDatabaseIndex == m_databases.size() - 1)
		changeActiveCategoryTo(0);
	else
		changeActiveCategoryTo(m_curDatabaseIndex + 1);
}

void MainWindow::onPrevCategory()
{
	if(m_curDatabaseIndex > 0)
		changeActiveCategoryTo(m_curDatabaseIndex - 1);
	else
		changeActiveCategoryTo(m_databases.size() - 1);
}