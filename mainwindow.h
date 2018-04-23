#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "addedit.h"
#include <QMainWindow>
#include <QStandardItem>
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
#include <QObject>
#include <QDate>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QHBoxLayout *hLayout;
    QRadioButton *all;
    QRadioButton *Overdue;
    QRadioButton *Today;
    QRadioButton *ThisWeek;
    QCheckBox *NotCompleted;
    QVBoxLayout *vLayout;
    QTableView *table;
    QStandardItemModel* items;
    QHBoxLayout *bottom;
    QPushButton *Add;
    QPushButton *Save;
    struct Task
    {
        int complete;
        QString title;
        QString description;
        QDate date;
    };

    QStandardItem* AddItem();

private slots:
    void test();

};

#endif // MAINWINDOW_H
