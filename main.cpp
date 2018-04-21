#include "mainwindow.h"
#include <QApplication>
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


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget();
    MainWindow mn = new MainWindow(window);
    window->show();


    // Event loop
    return app.exec();
}

