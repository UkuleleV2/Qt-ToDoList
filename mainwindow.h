#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "addedit.h"
#include "task.h"
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
    QRadioButton *All;
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
    QList<Task*> list;
    QStandardItem* AddItem();
    int SetFile(QString path);
    void setItem(int row,int item);
    void CreateUI();
private slots:
    void AddButton();
    void SaveButton();
    void EditRow(QModelIndex d);
    void AllSelected();
    void OverdueSelected();
    void TodaySelected();
    void ThisWeekSelected();
    void NotCompletedCheck();

};

#endif // MAINWINDOW_H
