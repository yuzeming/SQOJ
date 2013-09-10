#include "probmodel.h"
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDir>
QString ProbModel::HTMLDIR = QString();

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
    q.prepare("SELECT id,show FROM problem WHERE name=:n LIMIT 1");
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
    QFile html(QDir::cleanPath(HTMLDIR)+name+"/index.html");
    if (html.exists())
        return html.readAll();
    return "404 NOT FOUND";
}

QString ProbModel::readConf()
{
    if (name=="")   return "";
    QFile json(QDir::cleanPath(HTMLDIR)+name+"/config.json");
    if (json.exists())
        return json.readAll();
    return "";
}

QStringList ProbModel::GetList(int page, int item)
{
    QStringList ret;
    QSqlQuery q;
    q.prepare("SELECT name FROM problem LIMIT :item OFFSET :page");
    q.bindValue(":item",item);
    q.bindValue(":page",(page-1)*item);
    q.exec();
    while (q.next())
        ret.push_back(q.value(0).toString());
    return ret;
}
