#include "task.h"
#include <QString>

Task::Task()
{
    this->duedate="";
    this->title="";
    this->description="";
    this->complete=0;
}
Task::Task(QString date_arg, QString title_arg, QString description_arg, int complete_arg)
{
    this->duedate=date_arg;
    this->title=title;
    this->description=description_arg;
    this->complete=complete_arg;
}
Task::~Task()
{

}
int Task::getComplete()
{
    return this->complete;
}
QString Task::getTitle()
{
    return this->title;
}
QString Task::getDueDate()
{
    return this->duedate;
}
QString Task::getDescription()
{
    return this->description;
}
