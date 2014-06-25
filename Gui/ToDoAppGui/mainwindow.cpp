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

	//Category events
	QObject::connect(ui->lineEditCategory, SIGNAL(textChanged(QString)), this, SLOT(onCategoryNameChanged(QString)));
	QObject::connect(ui->buttonNext, SIGNAL(clicked()), this, SLOT(onNextCategory()));
	QObject::connect(ui->buttonPrevious, SIGNAL(clicked()), this, SLOT(onPrevCategory()));
	
	//ToDoApp events
	QObject::connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(onSave()));
	QObject::connect(ui->actionSaveTo, SIGNAL(triggered()), this, SLOT(onSaveTo()));
	QObject::connect(ui->actionSaveAll, SIGNAL(triggered()), this, SLOT(onSaveAll()));
	QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onSaveAll()));

	//Category menu events
	QObject::connect(ui->actionAddCategory, SIGNAL(triggered()), this, SLOT(onAddCategory()));
	QObject::connect(ui->menuChooseCategory, SIGNAL(aboutToShow()), this, SLOT(onChooseCategory()));
	QObject::connect(ui->menuChooseCategory, SIGNAL(aboutToHide()), this, SLOT(onHideChooseCategory()));

	//Settings events
	QObject::connect(ui->actionShowChecked, SIGNAL(toggled(bool)), this, SLOT(onShowChecked(bool)));

	//Other
	QObject::connect(ui->buttonAddItem, SIGNAL(clicked()), this, SLOT(onAddItem()));
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
    vector<string> * filesInDir = new vector<string>;

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

void MainWindow::removeChildrenOf(QLayout * layout)
{
	QLayoutItem* child;

	if(layout)
    while(layout->count()!=0)
    {
        child = layout->takeAt(0);
		if(typeid(child) == typeid(QFrame))
		{
			qDeleteAll(child->widget()->layout()->children());
			delete child;
		}
        
		if(child->layout() != 0)
        {
            removeChildrenOf(child->layout());
        }
        else if(child->widget() != 0)
        {
            delete child->widget();
        }

        delete child;
    }
}

void MainWindow::loadItems()
{
	//delete old Items
	if(ui->scrollAreaItems != NULL)
		removeChildrenOf(ui->scrollAreaItems->widget()->layout());

	//load new Items
	vector<ToDoData*> data = m_databases.at(m_curDatabaseIndex)->getAllEntries();

	for(int i=0; i< data.size(); i++)
	{
		if(!m_showCheckedItems)
		{
			if(!data.at(i)->isDone())
				addItemForData(data.at(i));
		}else
			addItemForData(data.at(i));
	}

	//add spacer
	QSpacerItem * spacer = new QSpacerItem(20,20, QSizePolicy::Expanding);
	ui->scrollAreaItems->widget()->layout()->addItem(spacer);
	ui->scrollAreaItems->update();
}

void MainWindow::addItemForData(ToDoData* data)
{
	QVBoxLayout * layout = static_cast<QVBoxLayout*>(ui->scrollAreaItems->widget()->layout());

	layout->insertWidget(0, MainWindow::createItemFrom(data));
}

void MainWindow::saveItemsToCurDatabase()
{
	ToDoDatabase * curDB = m_databases.at(m_curDatabaseIndex);

	curDB->removeAllEntries();
	QLayout * layout = ui->scrollAreaWidgetContents->layout();
	for(int i=0; i< layout->count(); i++)
	{
		QWidget * item = layout->itemAt(i)->widget();
		if(dynamic_cast<QFrame *>(item))
		{
			QLayout * layout = item->layout();
			curDB->add(new ToDoData(
				static_cast<QLineEdit *>(layout->itemAt(0)->widget())->text().toStdString(),
				static_cast<QLineEdit *>(layout->itemAt(1)->widget())->text().toStdString(),
				static_cast<QCheckBox *>(layout->itemAt(2)->widget())->isChecked()));
		}
	}
}

void MainWindow::changeActiveCategoryTo(int index)
{
	saveItemsToCurDatabase();

	//load new data
	m_curDatabaseIndex = index;

	//load data into UI
	ui->lineEditCategory->setText(m_databases.at(index)->getName().c_str());
	//loadITems
	loadItems();
}

int MainWindow::getCategoryIndexForName(string name)
{
	for(int i=0;i < m_databases.size(); i++)
	{
		if(m_databases.at(i)->getName().compare(name) == 0)
			return i;
	}

	return -1;
}


/****
		static methods

****/

QFrame* MainWindow::createItemFrom(ToDoData * data)
{
	return MainWindow::createItem(data->getTitle(), 
								  data->getDescription(), 
								  data->isDone());
}

QFrame* MainWindow::createItem()
{
	return MainWindow::createItem("lineEditTitle", "lineEditDate", false);
}

QFrame* MainWindow::createItem(string title, string description, bool done)
{
	QFrame * frame = new QFrame();
	frame->setMaximumHeight(30);
	QHBoxLayout * layout = new QHBoxLayout();
	layout->setContentsMargins(5, 5, 5, 5);

	//set max height to 20
	QLineEdit * le = new QLineEdit(title.c_str());
	le->setMaximumSize(QSize(1000,20));
	layout->addWidget(le);
	QLineEdit * le2 = new QLineEdit(description.c_str());
	le2->setMaximumSize(QSize(100, 20));
	layout->addWidget(le2);
	QCheckBox * chb = new QCheckBox();
	chb->setChecked(done);
	layout->addWidget(chb);

	frame->setLayout(layout);

	return frame;
}


/****
		Signals

****/

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

void MainWindow::onSave()
{
	m_databases.at(m_curDatabaseIndex)->saveData();
}

void MainWindow::onSaveTo()
{
	//open path picker
	//m_databases.at(m_curDatabaseIndex)->saveDataTo(path.toStdString());
}

void MainWindow::onSaveAll()
{
	for(int i=0; i<m_databases.size(); i++)
		m_databases.at(i)->saveData();
}

void MainWindow::onAddCategory()
{
	cout << "add some new category";
}

void MainWindow::onChooseCategory()
{
	//iterate over categories and add an action for each
	for(int i=0; i<m_databases.size(); i++)
	{
		QAction * newAction = new QAction(QString::fromStdString(m_databases.at(i)->getName()), ui->menuChooseCategory);
		
		//connect onclick with some function
		//WHATS WRONG HERE!?
		QObject::connect(newAction, SIGNAL(triggered()), this, SLOT(onCategoryChoosen()));

		ui->menuChooseCategory->addAction(newAction);
	}
}

void MainWindow::onHideChooseCategory()
{
	ui->menuChooseCategory->clear();
}

void MainWindow::onCategoryChoosen()
{
	int index = getCategoryIndexForName(dynamic_cast<QAction*>(sender())->text().toStdString());
	
	if(index >= 0)
		changeActiveCategoryTo(index);
}

void MainWindow::onShowChecked(bool checked)
{
	m_showCheckedItems = checked;

	/***
		hide all checked items.
		update view.
	***/
	loadItems();
	ui->scrollAreaItems->update();
}

void MainWindow::onAddItem()
{
	QVBoxLayout *layout = static_cast<QVBoxLayout*>(ui->scrollAreaItems->widget()->layout());
	layout->insertWidget(0, MainWindow::createItem());
}
