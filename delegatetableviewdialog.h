#ifndef DELEGATETABLEVIEWDIALOG_H
#define DELEGATETABLEVIEWDIALOG_H

#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

namespace Ui {
class DelegateTableViewDialog;
}

class DelegateTableViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelegateTableViewDialog(QWidget *parent = 0);
    ~DelegateTableViewDialog();

private:
    Ui::DelegateTableViewDialog *ui;

    // QStandardItemModel provides a classic
    // item-based approach to working with the model.
    QStandardItemModel *model;
};

#endif // DELEGATETABLEVIEWDIALOG_H
