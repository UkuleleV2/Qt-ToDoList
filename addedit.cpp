#include "addedit.h"
#include "mainwindow.h"
#include "ui_addedit.h"
#include <QDebug>
#include <QString>
#include <QVariant>
#include <QDate>
#include <QWidget>
#include <QMessageBox>
AddEdit::AddEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEdit)
{

    ui->setupUi(this);
    ui->slider->setRange(0,100);

}
AddEdit::AddEdit(QModelIndex index,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEdit)
{
    ui->setupUi(this);
    ui->slider->setRange(0,100);
    QDate date = date.fromString(index.sibling(index.row(),0).data().toString(),"yyyy-MM-dd");
    ui->title->setText(index.sibling(index.row(),1).data().toString());
    ui->description->setText(index.sibling(index.row(),3).data().toString());
    ui->date->setDate(date);
    ui->slider->setValue(index.sibling(index.row(),2).data().toInt());
}

AddEdit::~AddEdit()
{
    delete ui;
}

void AddEdit::on_pushButton_clicked()
{
    if (ui->description->toPlainText() != "" && ui->title->text() != "" )
    {
        task = new Task(ui->date->date(),ui->title->text(),ui->slider->value(),ui->description->toPlainText());
        this->close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Title or description cannot be empty.");
        msgBox.exec();
    }

}
void AddEdit::closeEvent(QCloseEvent *bar)
{
    this->on_pushButton_2_clicked();
}
Task* AddEdit::getTask()
{
    return task;
}

void AddEdit::on_pushButton_2_clicked()
{
    task = nullptr;
    this->close();
}
