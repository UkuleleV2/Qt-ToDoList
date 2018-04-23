#include "task.h"

    Task::Task()
    {
        this->title = "No info";
        this->complete = 0;
        this->description = "No info";
        this->date = QDate(1996,1,1);

    }

    Task::Task(QDate date_arg, QString title_arg, int complete_arg, QString description_arg)
    {
  /*      QString year,month,day;
        this->date = date_arg;
        this->title = title_arg;
        this->complete = complete_arg;
        this->description = description_arg;
        year = date_arg.substring(0,4);
        month = date_arg.substring(5,7);
        day = date_arg.substring(8);
        this->date = QDate.of(Integer.parseInt(year),Integer.parseInt(month),Integer.parseInt(day));*/
    }
 /*   void Task::ModifyTask(String date_arg, String title_arg, int complete_arg, String description_arg)
    {
        String year,month,day;
        this->due_date = date_arg;// new String(date_arg);
        this->title = title_arg;
        this->complete = complete_arg;
        this->description = description_arg;
        year = date_arg.substring(0,4);
        month = date_arg.substring(5,7);
        day = date_arg.substring(8);
        this->date = QDate.of(Integer.parseInt(year),Integer.parseInt(month),Integer.parseInt(day));
        this->check = new CheckBox();
        this->check.setDisable(true);
        if (complete_arg == 100)
            this->check.setSelected(true);
        else
            this->check.setSelected(false);
    }*/
    QDate Task::getDate()
    {
        return this->date;
    }
    void Task::setDate(QDate date)
    {
        this->date = date;
    }
    QString Task::getTitle()
    {
        return this->title;
    }

    void Task::setTitle(QString title_arg)
    {
        this->title = title_arg;
    }

    int Task::getComplete()
    {
        return this->complete;
    }

    void Task::setComplete(int complete_arg)
    {
        this->complete = complete_arg;
    }

    QString Task::getDescription()
    {
        return this->description;
    }

    void Task::setDescription(QString description_arg)
    {
        this->description = description_arg;
    }

