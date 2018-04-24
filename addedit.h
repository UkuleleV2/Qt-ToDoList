#ifndef ADDEDIT_H
#define ADDEDIT_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class AddEdit;
}

class AddEdit : public QDialog
{
    Q_OBJECT

public:
    explicit AddEdit(QWidget *parent = 0);
    ~AddEdit();
    test();
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddEdit *ui;
};

#endif // ADDEDIT_H
