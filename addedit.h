#ifndef ADDEDIT_H
#define ADDEDIT_H

#include <QDialog>
#include "mainwindow.h"
#include "task.h"
#include <QModelIndex>
#include <QPushButton>
#include <QList>
#include <QString>
namespace Ui {
class AddEdit;
}

class AddEdit : public QDialog
{
    Q_OBJECT

public:
    explicit AddEdit(QWidget *parent = 0);
    explicit AddEdit(QModelIndex index,QPushButton *TaskSave,QWidget *parent = 0);
    ~AddEdit();
    Task* getTask();
    QString test;
    Task* task;
    void SetItems(QModelIndex index);
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddEdit *ui;
};

#endif // ADDEDIT_H
