#ifndef ADDOREDIT_H
#define ADDOREDIT_H

#include <QWidget>

namespace Ui {
class AddOrEdit;
}

class AddOrEdit : public QWidget
{
    Q_OBJECT

public:
    AddOrEdit(QWidget *parent = 0);
    ~AddOrEdit();

private:
    Ui::AddOrEdit *ui;
};

#endif // ADDOREDIT_H
