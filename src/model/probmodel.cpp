#include "probmodel.h"
#include <QtSql/QSqlQuery>
#include <QStringList>

ProbModel::ProbModel(QString _name, int _show)
{
    QSqlQuery query;
    QStringList tabls=db.tables();
    if (tabls.count("problem")==0)
    {
        query.exec("CREATE TABLE problem("
                   "id INTEGER PRIMARY KEY,"
                   "show INTEGER DEFAULT 1,"
                   "name VARCHAR(20) UNIQUE"
                   ") ");
        ProbModel("test",1).Save();
    }
    name = _name;
    show = _show;
    id = 0;
}

ProbModel& ProbModel::Find(QString name)
{
    QSqlQuery q;
    q.prepare("SELECT id,show FORM problem WHERE name=:n LIMIT 1");
    q.bindValue(":n",name);
    q.exec();
    ProbModel * ret=new ProbModel();
    if (q.next())
    {
        ret->id=q.value(0).toInt();
        ret->name=name;
        ret->show=q.value(1).toInt();
    }
    return *ret;
}

bool ProbModel::Save()
{
    QSqlQuery q;
    if (id != 0)
    {
        q.prepare("UPDATA problem SET name =:n ,show = :s WHERE id = :i");
        q.bindValue(":i",id);
    }
    else
        q.prepare("INSERT INTO problem (name,show) VALUES (:n,:s)");
    q.bindValue(":n",name);
    q.bindValue(":s",show);
    return q.exec();
}


QString ProbModel::readHTML()
{
    if (name=="")   return "Set NAME First!";

}
