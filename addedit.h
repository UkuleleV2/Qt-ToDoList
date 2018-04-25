#ifndef ADDEDIT_H
#define ADDEDIT_H

#include <QDialog>
#include "mainwindow.h"
#include "task.h"
#include <QModelIndex>
#include <QPushButton>
#include <QList>
#include <QString>
#include <QCloseEvent>
namespace Ui {
class AddEdit;
}

class AddEdit : public QDialog
{
    Q_OBJECT

public:
    explicit AddEdit(QWidget *parent = 0);
    explicit AddEdit(QModelIndex index,QWidget *parent = 0);
    ~AddEdit();
    Task* getTask();
    void closeEvent(QCloseEvent *bar);
    Task* task;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::AddEdit *ui;
};

#endif // ADDEDIT_H
