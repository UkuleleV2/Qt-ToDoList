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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
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



    // Horizontal layout with 3 buttons
    QHBoxLayout *hLayout = new QHBoxLayout;
    QRadioButton *all = new QRadioButton("All");
    QRadioButton *Overdue = new QRadioButton("Overdue");
    QRadioButton *Today = new QRadioButton("Today");
    QRadioButton *ThisWeek = new QRadioButton("ThisWeek");
    QCheckBox *NotCompleted = new QCheckBox("Not Completed");
    hLayout->addWidget(all);
    hLayout->addWidget(Overdue);
    hLayout->addWidget(Today);
    hLayout->addWidget(ThisWeek);
    hLayout->addWidget(NotCompleted);

    // Vertical layout
    QVBoxLayout *vLayout = new QVBoxLayout;
    QTableView *table = new QTableView;
    vLayout->addWidget(table);
    QHBoxLayout *bottom = new QHBoxLayout;
    QPushButton *Add = new QPushButton("Add");
    QPushButton *Save = new QPushButton("Save");
    bottom->addWidget(Add);
    bottom->addWidget(Save);
    // Outer Layer
    QVBoxLayout *mainLayout = new QVBoxLayout;

    // Add the previous two inner layouts
    mainLayout->addLayout(hLayout);
    mainLayout->addLayout(vLayout);
    mainLayout->addLayout(bottom);

    //table->setModel(model);
    // Create a widget


    // Set the outer layout as a main layout
    // of the widget
    parent->setLayout(mainLayout);

    qDebug() << "Created:";
    // Window title
    parent->setWindowTitle("To Do list");
    QObject::connect(Add, SIGNAL (released()), this, SLOT (test()));

}

MainWindow::~MainWindow()
{

}
void test()
{
       qDebug() << "Test button:";
}

