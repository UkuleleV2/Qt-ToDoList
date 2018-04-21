#include "addoredit.h"
#include "ui_addoredit.h"

AddOrEdit::AddOrEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddOrEdit)
{
    ui->setupUi(this);
}

AddOrEdit::~AddOrEdit()
{
    delete ui;
}
