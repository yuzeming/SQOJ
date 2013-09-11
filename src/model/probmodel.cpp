#include "probmodel.h"
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDir>

QDir ProbModel::ProbRoot = QDir();

ProbModel::ProbModel(QString _name, int _show) : ModelBase()
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

ProbModel::ProbModel(const ProbModel &copy) : ModelBase(copy)
{
    name=copy.name;
    id=copy.id;
    show=copy.show;
}

ProbModel& ProbModel::Find(QString name)
{
    QSqlQuery q;
    ProbModel * ret=new ProbModel();
    q.prepare("SELECT id,show FROM problem WHERE name=:n LIMIT 1");
    q.bindValue(":n",name);
    q.exec();
    if (q.next())
    {
        ret->id=q.value(0).toInt();
        ret->name=name;
        ret->show=q.value(1).toInt();
    }
    return *ret;
}

ProbModel &ProbModel::FindByID(int id)
{
    QSqlQuery q;
    ProbModel * ret=new ProbModel();
    q.prepare("SELECT name,show FROM problem WHERE id=:id LIMIT 1");
    q.bindValue(":id",id);
    q.exec();
    if (q.next())
    {
        ret->id=id;
        ret->name=q.value(0).toString();
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

QString GetFileContent(QString fname)
{
    QFile f(fname);
    if (f.exists())
    {
        f.open(QIODevice::ReadOnly);
        return f.readAll();
    }
    return "404 NOT FOUND";
}

QString ProbModel::readHTML()
{
    if (name=="")   return "Set NAME First!";
    QDir f((ProbRoot));
    if (!f.cd(name))    return "Dir Not Find";
    return GetFileContent(f.filePath("index.html"));
}

QString ProbModel::readConf()
{
    if (name=="")   return "Set NAME First!";
    QDir f((ProbRoot));
    if (!f.cd(name))    return "Dir Not Find";
    return GetFileContent(f.filePath("config.json"));
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
