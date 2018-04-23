#include "addedit.h"
#include "ui_addedit.h"

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
