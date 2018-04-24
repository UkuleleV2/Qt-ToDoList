#include "addedit.h"
#include "mainwindow.h"
#include "ui_addedit.h"
#include <QDebug>
AddEdit::AddEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEdit)
{

    ui->setupUi(this);
}

AddEdit::~AddEdit()
{
    delete ui;
}

void AddEdit::on_pushButton_clicked()
{

}
void AddEdit::test()
{

}
