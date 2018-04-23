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
    QDate a(1995, 5, 17);
    QList<Task> list;
    const Task* lel;
    lel= new Task();
    list.append(lel);
    qDebug() << list[0].getDate();
    items = new QStandardItemModel(0,4);
    items->setHeaderData(0, Qt::Horizontal, QObject::tr("DueDate"));
    items->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    items->setHeaderData(2, Qt::Horizontal, QObject::tr("% complete"));
    items->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    QFile file("C:/test/in.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
         qDebug() << "Cannot open file";
    QTextStream in(&file);
    QString line = in.readLine();
    int i = 0;
    int row = 0;
    int our_sign = 0;
    int next_sign = 0;
    QString info[6];
    while (!line.isNull() && line != "") {
        line = in.readLine();
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
        for (int column = 1; column <= 4; ++column)
        {
            QStandardItem* item = new QStandardItem(info[column]);
            items->setItem(row, column-1, item);
        }
        row++;
    }

  //
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
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Add the previous two inner layouts
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(vLayout);
    mainLayout->addLayout(bottom);

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
    QObject::connect(Add, SIGNAL (clicked()), this, SLOT (AddButton()));
    QObject::connect(sm, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
                this, SLOT(SaveButton()));
    connect(sm, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(EditRow(QModelIndex)));
    QObject::connect(All, SIGNAL (clicked()), this, SLOT (AllSelected()));
    QObject::connect(Overdue, SIGNAL (clicked()), this, SLOT (OverdueSelected()));
    QObject::connect(Today, SIGNAL (clicked()), this, SLOT (TodaySelected()));
    QObject::connect(ThisWeek, SIGNAL (clicked()), this, SLOT (ThisWeekSelected()));
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
void MainWindow::AllSelected()
{
    qDebug() << "Test:";
}
void MainWindow::OverdueSelected()
{
qDebug() << items->item(1,1)->text();

}
void MainWindow::TodaySelected()
{
qDebug() << "Test:";
}
void MainWindow::ThisWeekSelected()
{
qDebug() << "Test:";
}

MainWindow::~MainWindow()
{
qDebug() << "Test:";
}


