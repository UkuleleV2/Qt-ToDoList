#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QtDebug>
#include <QFile>
#include <QList>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    items = new QStandardItemModel(0,4);
    table = new QTableView;
    int z = SetFile("C:/test/in.txt");
    if (z == -1)
    {
        qDebug() << "File is not in correct format";
    }
    else if( z == 1)
    {
        qDebug() << "Cannot open file";
    }

    this->CreateUI();
    items->setHeaderData(0, Qt::Horizontal, QObject::tr("DueDate"));
    items->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    items->setHeaderData(2, Qt::Horizontal, QObject::tr("% complete"));
    items->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
  //  table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setModel(items);


    connect(Add, SIGNAL (clicked()), this, SLOT (AddButton()));
    connect(table,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(EditRow(QModelIndex)));
    connect(All, SIGNAL (clicked()), this, SLOT (AllSelected()));
    connect(Overdue, SIGNAL (clicked()), this, SLOT (OverdueSelected()));
    connect(Today, SIGNAL (clicked()), this, SLOT (TodaySelected()));
    connect(ThisWeek, SIGNAL (clicked()), this, SLOT (ThisWeekSelected()));
    connect(NotCompleted, SIGNAL (clicked()),this, SLOT(NotCompletedCheck()));

    All->click();
//
}
void MainWindow::test()
{
    qDebug() << "echo";
}
void MainWindow::CreateUI()
{
    //Menu Bar
    menu = new QMenuBar(this);
    fileselect = new QMenu(tr("&File"), this);
    menu->addMenu(fileselect);

    // Horizontal layout with 4 buttons and checkbox
    QHBoxLayout *hLayout = new QHBoxLayout;
    All = new QRadioButton("All");
    Overdue = new QRadioButton("Overdue");
    Today = new QRadioButton("Today");
    ThisWeek = new QRadioButton("ThisWeek");
    NotCompleted = new QCheckBox("Not Completed");
    hLayout->addWidget(All);
    hLayout->addWidget(Overdue);
    hLayout->addWidget(Today);
    hLayout->addWidget(ThisWeek);
    hLayout->addWidget(NotCompleted);

    // creating layout
    QVBoxLayout * vLayout = new QVBoxLayout;
    vLayout->setMenuBar(menu);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(table);
    bottom = new QHBoxLayout;
    Add = new QPushButton("Add");
    Save = new QPushButton("Save");
    bottom->addWidget(Add);
    bottom->addWidget(Save);
    // Outer Layer

    // Add the previous two inner layouts
    vLayout->addLayout(bottom);
    // Create a widget
    QWidget *window = new QWidget();
    // Set the outer layout as a main layout
    // of the widget
    window->setLayout(vLayout);
    // Window title
    window->setWindowTitle("To Do list");
    window->show();
}
int MainWindow::SetFile(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "Cannot open file";
        return 1;
    }
    QTextStream in(&file);
    QString line = in.readLine();
    if (line != "TASKLIST^^^")
    {
        return -1;
    }
    line = in.readLine();
    int i = 0;
    int our_sign = 0;
    int next_sign = 0;
    QString info[6];
    while (!line.isNull() && line != "") {
        i= 0;
        our_sign = 0;
        next_sign = line.indexOf('|', our_sign+1);
        while (next_sign != -1)
            {
                info[i] = line.mid(our_sign+1,next_sign-our_sign-1);
                our_sign = next_sign;
                next_sign = line.indexOf('|', our_sign+1);
                i++;
            }
        info[i] = line.mid(our_sign+1);
        QDate date;
        Task* temp = new Task(date.fromString(info[1],"yyyy-MM-dd"),info[2],info[3].toInt(),info[4]);
        list.append(temp);
        line = in.readLine();
    }
    file.close();
    return 0;
}
void MainWindow::AddButton()
{
    AddEdit* addpoint = new AddEdit(this);
    addpoint->show();
    if (addpoint->exec())
    {
        qDebug() << "test";
    }
    list.append(addpoint->getTask());
    this->NotCompletedCheck();
}
void MainWindow::SaveButton()
{
    qDebug() << "Save button:";
}
void MainWindow::EditRow(QModelIndex d)
{
    AddEdit* addpoint = new AddEdit(d,TaskSave,this);
    addpoint->show();
    if (addpoint->exec())
    {
        qDebug() << "test";
    }
  //  Task* task = AddEdit.setTask();
    qDebug() << addpoint->getTask()->getComplete();
}
void MainWindow::NotCompletedCheck()
{
    if (All->isChecked())
        this->AllSelected();
    else if(Overdue->isChecked())
        this->OverdueSelected();
    else if(Today->isChecked())
        this->TodaySelected();
    else if(ThisWeek->isChecked())
        this->ThisWeekSelected();
}
void MainWindow::AllSelected()
{
    items->clear();
    int row = 0;
    if (NotCompleted->isChecked())
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getComplete()<100)
            {
                this->setItem(row,i);
                row++;
            }

        }
    }
    else
    {
        for (int i = 0;i<list.size();i++)
        {
                this->setItem(i,i);
        }
    }


}

void MainWindow::OverdueSelected()
{
    items->clear();
    int row = 0;
    QDate current = QDate::currentDate();
    if (NotCompleted->isChecked())
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getDate()< current && list[i]->getComplete()<100)
            {
                this->setItem(row,i);
                row++;
            }

        }
    }
    else
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getDate()< current)
            {
                this->setItem(row,i);
                row++;
            }

        }
    }

}
void MainWindow::TodaySelected()
{
    items->clear();
    int row = 0;
    QDate current = QDate::currentDate();
    if (NotCompleted->isChecked())
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getDate()== current && list[i]->getComplete()<100)
            {
                this->setItem(row,i);
                row++;
            }
        }
    }
    else
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getDate()== current)
            {
                this->setItem(row,i);
                row++;
            }
        }
    }
}
void MainWindow::ThisWeekSelected()
{
        items->clear();
        int row = 0;
        QDate current = QDate::currentDate();
        if (NotCompleted->isChecked())
        {
            for (int i = 0;i<list.size();i++)
            {
                if (list[i]->getDate().weekNumber() == current.weekNumber() && list[i]->getComplete()<100)
                {
                    this->setItem(row,i);
                    row++;
                }
            }
        }
        else
        {
            for (int i = 0;i<list.size();i++)
            {
                if (list[i]->getDate().weekNumber() == current.weekNumber())
                {
                    this->setItem(row,i);
                    row++;
                }
            }
        }
}
void MainWindow::setItem(int row, int item)
{
    QStandardItem* date = new QStandardItem(list[item]->getDateString());
    QStandardItem* title = new QStandardItem(list[item]->getTitle());
    QStandardItem* complete = new QStandardItem(list[item]->getCompleteString());
    QStandardItem* description = new QStandardItem(list[item]->getDescription());
    items->setItem(row, 0, date);
    items->setItem(row, 1, title);
    items->setItem(row, 2, complete);
    items->setItem(row, 3, description);
}
MainWindow::~MainWindow()
{
    qDebug() << "Closing";
}


