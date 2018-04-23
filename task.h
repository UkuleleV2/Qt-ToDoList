#ifndef TASK_H
#define TASK_H
#include <QString>
#include <QDate>



class Task
{
    QString title;
    int complete;
    QString description;
    QDate date;

public:
    Task();
    Task(QDate date_arg, QString title_arg, int complete_arg, QString description_arg);

    QDate getDate();
    QString getTitle();
    int getComplete();
    QString getDescription();
    void setDate(QDate date);
    void setTitle(QString title_arg);
    void setComplete(int complete_arg);
    void setDescription(QString description_arg);
};
#endif // TASK_H
