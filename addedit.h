#ifndef ADDEDIT_H
#define ADDEDIT_H

#include <QDialog>

namespace Ui {
class AddEdit;
}

class AddEdit : public QDialog
{
    Q_OBJECT

public:
    explicit AddEdit(QWidget *parent = 0);
    ~AddEdit();

private:
    Ui::AddEdit *ui;
};

#endif // ADDEDIT_H
