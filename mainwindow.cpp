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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    items = new QStandardItemModel(0,4);
    QFile file("C:/test/in.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
         qDebug() << "Cannot open file";
    QTextStream in(&file);
    QString line = in.readLine();
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
        qDebug() << info[3];
        QDate date;
        Task* temp = new Task(date.fromString(info[1],"yyyy-MM-dd"),info[2],info[3].toInt(),info[4]);
        list.append(temp);
        line = in.readLine();
    }

    // Horizontal layout with 3 buttons
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

    // Vertical layout
    QVBoxLayout * vLayout = new QVBoxLayout;
    table = new QTableView;
    vLayout->addWidget(table);
    bottom = new QHBoxLayout;
    Add = new QPushButton("Add");
    Save = new QPushButton("Save");
    bottom->addWidget(Add);
    bottom->addWidget(Save);
    // Outer Layer

    QVBoxLayout *mainLayout = new QVBoxLayout;
    // Add the previous two inner layouts
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(vLayout);
    mainLayout->addLayout(bottom);
    items->setHeaderData(0, Qt::Horizontal, QObject::tr("DueDate"));
    items->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    items->setHeaderData(2, Qt::Horizontal, QObject::tr("% complete"));
    items->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setModel(items);

    // Create a widget

    QWidget *window = new QWidget();
    // Set the outer layout as a main layout
    // of the widget
    window->setLayout(mainLayout);
    // Window title
    window->setWindowTitle("To Do list");
    window->show();
    QItemSelectionModel *sm = table->selectionModel();
    connect(Add, SIGNAL (clicked()), this, SLOT (AddButton()));
    connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(SaveButton()));
    connect(sm, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(EditRow(QModelIndex)));
    connect(All, SIGNAL (clicked()), this, SLOT (AllSelected()));
    connect(Overdue, SIGNAL (clicked()), this, SLOT (OverdueSelected()));
    connect(Today, SIGNAL (clicked()), this, SLOT (TodaySelected()));
    connect(ThisWeek, SIGNAL (clicked()), this, SLOT (ThisWeekSelected()));
    connect(NotCompleted, SIGNAL (clicked()),this, SLOT(NotCompletedCheck()));

  //  all->isEnabled()
    All->click();
    file.close();
}
void MainWindow::AddButton()
{
    qDebug() << "Add button:";
    AddEdit* addpoint = new AddEdit(this);
    addpoint->show();
}
void MainWindow::SaveButton()
{
    qDebug() << "Save button:";
}
void MainWindow::EditRow(QModelIndex d)
{
    qDebug() << "Edit row:";
    qDebug() << d;
    AddEdit* addpoint = new AddEdit(this);
    addpoint->show();
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
    qDebug() << "Test:";
    if (NotCompleted->isChecked())
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getComplete()<100)
            {
                QStandardItem* date = new QStandardItem(list[i]->getDateString());
                QStandardItem* title = new QStandardItem(list[i]->getTitle());
                QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                QStandardItem* description = new QStandardItem(list[i]->getDescription());
                items->setItem(row, 0, date);
                items->setItem(row, 1, title);
                items->setItem(row, 2, complete);
                items->setItem(row, 3, description);
                row++;
            }

        }
    }
    else
    {
        for (int i = 0;i<list.size();i++)
        {
                QStandardItem* date = new QStandardItem(list[i]->getDateString());
                QStandardItem* title = new QStandardItem(list[i]->getTitle());
                QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                QStandardItem* description = new QStandardItem(list[i]->getDescription());
                items->setItem(i, 0, date);
                items->setItem(i, 1, title);
                items->setItem(i, 2, complete);
                items->setItem(i, 3, description);

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
                QStandardItem* date = new QStandardItem(list[i]->getDateString());
                QStandardItem* title = new QStandardItem(list[i]->getTitle());
                QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                QStandardItem* description = new QStandardItem(list[i]->getDescription());
                items->setItem(row, 0, date);
                items->setItem(row, 1, title);
                items->setItem(row, 2, complete);
                items->setItem(row, 3, description);
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
                QStandardItem* date = new QStandardItem(list[i]->getDateString());
                QStandardItem* title = new QStandardItem(list[i]->getTitle());
                QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                QStandardItem* description = new QStandardItem(list[i]->getDescription());
                items->setItem(row, 0, date);
                items->setItem(row, 1, title);
                items->setItem(row, 2, complete);
                items->setItem(row, 3, description);
                row++;
            }

        }
    }

}
void MainWindow::TodaySelected()
{
    qDebug() << "Test:";
    items->clear();
    int row = 0;
    QDate current = QDate::currentDate();
    if (NotCompleted->isChecked())
    {
        for (int i = 0;i<list.size();i++)
        {
            if (list[i]->getDate()== current && list[i]->getComplete()<100)
            {
                QStandardItem* date = new QStandardItem(list[i]->getDateString());
                QStandardItem* title = new QStandardItem(list[i]->getTitle());
                QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                QStandardItem* description = new QStandardItem(list[i]->getDescription());
                items->setItem(row, 0, date);
                items->setItem(row, 1, title);
                items->setItem(row, 2, complete);
                items->setItem(row, 3, description);
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
                QStandardItem* date = new QStandardItem(list[i]->getDateString());
                QStandardItem* title = new QStandardItem(list[i]->getTitle());
                QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                QStandardItem* description = new QStandardItem(list[i]->getDescription());
                items->setItem(row, 0, date);
                items->setItem(row, 1, title);
                items->setItem(row, 2, complete);
                items->setItem(row, 3, description);
                row++;
            }
        }
    }
}
void MainWindow::ThisWeekSelected()
{
    qDebug() << "Test:";
        items->clear();
        int row = 0;
        QDate current = QDate::currentDate();
        if (NotCompleted->isChecked())
        {
            for (int i = 0;i<list.size();i++)
            {
                if (list[i]->getDate().weekNumber() == current.weekNumber() && list[i]->getComplete()<100)
                {
                    QStandardItem* date = new QStandardItem(list[i]->getDateString());
                    QStandardItem* title = new QStandardItem(list[i]->getTitle());
                    QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                    QStandardItem* description = new QStandardItem(list[i]->getDescription());
                    items->setItem(row, 0, date);
                    items->setItem(row, 1, title);
                    items->setItem(row, 2, complete);
                    items->setItem(row, 3, description);
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
                    QStandardItem* date = new QStandardItem(list[i]->getDateString());
                    QStandardItem* title = new QStandardItem(list[i]->getTitle());
                    QStandardItem* complete = new QStandardItem(list[i]->getCompleteString());
                    QStandardItem* description = new QStandardItem(list[i]->getDescription());
                    items->setItem(row, 0, date);
                    items->setItem(row, 1, title);
                    items->setItem(row, 2, complete);
                    items->setItem(row, 3, description);
                    row++;
                }
            }
        }
}
MainWindow::~MainWindow()
{
    qDebug() << "Closing";
}


