#include "mainwindow.h"
#include "addoredit.h"
#include <task.h>
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

/*   const int numRows = 10;
   const int numColumns = 10;

   QStandardItemModel* model = new QStandardItemModel(numRows, numColumns);
   for (int row = 0; row < numRows; ++row)
   {
       for (int column = 0; column < numColumns; ++column)
       {
           QString text = QString('A' + row) + QString::number(column + 1);
           QStandardItem* item = new QStandardItem(text);
           model->setItem(row, column, item);
       }
    }
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    QFile file("C:/test/in.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
         qDebug() << "Cannot open file";
    QTextStream in(&file);
    QString line = in.readLine();
    while (!line.isNull()) {
      //  process_line(line);
        line = in.readLine();
        qDebug() << line;
    }
    Task *ne = new Task();
 //   Task *we = new Task("Aaa","bbbb","cccc",7);
 //   qDebug() << we->getDescription();
    items = new QStandardItemModel();
    items->setRowCount(0);
    items->setColumnCount(4);
    items->setHeaderData(0, Qt::Horizontal, QObject::tr("DueDate"));
    items->setHeaderData(1, Qt::Horizontal, QObject::tr("Title"));
    items->setHeaderData(2, Qt::Horizontal, QObject::tr("% complete"));
    items->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));

    // Horizontal layout with 3 buttons
    QHBoxLayout *hLayout = new QHBoxLayout;
    all = new QRadioButton("All");
    Overdue = new QRadioButton("Overdue");
    Today = new QRadioButton("Today");
    ThisWeek = new QRadioButton("ThisWeek");
    NotCompleted = new QCheckBox("Not Completed");
    hLayout->addWidget(all);
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
    QObject::connect(Add, SIGNAL (released()), this, SLOT (test()));





    file.close();
}
void MainWindow::test()
{
       qDebug() << "Test button:";

}
MainWindow::~MainWindow()
{

}


