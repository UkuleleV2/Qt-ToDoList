#ifndef TASK_H
#define TASK_H

#include <QString>

class Task
{
    QString duedate;
    QString title;
    QString description;
    int complete;
public:
    Task();
    Task(QString date_arg, QString title_arg, QString description_arg, int complete_arg);
    ~Task();
    QString getDueDate();
    QString getTitle();
    QString getDescription();
    int getComplete();
};

#endif // TASK_H
