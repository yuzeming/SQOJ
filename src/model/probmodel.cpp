#include "probmodel.h"
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDir>

QDir ProbModel::ProbRoot = QDir();

ProbModel::ProbModel(QString _name, QString _title, int _show) : ModelBase()
{
    QSqlQuery query;
    QStringList tabls=db.tables();
    if (tabls.count("problem")==0)
    {
        query.exec("CREATE TABLE problem("
                   "id INTEGER PRIMARY KEY,"
                   "show INTEGER DEFAULT 1,"
                   "name VARCHAR(20) UNIQUE,"
                   "title TEXT"
                   ") ");
        ProbModel("test","测试",1).Save();
    }
    name = _name;
    show = _show;
    title = _title;
    id = 0;
}

ProbModel::ProbModel(const ProbModel &copy) : ModelBase(copy)
{
    name=copy.name;
    id=copy.id;
    show=copy.show;
    title=copy.title;
}

ProbModel& ProbModel::Find(QString name)
{
    QSqlQuery q;
    ProbModel * ret=new ProbModel();
    q.prepare("SELECT id,show,title FROM problem WHERE name=:n LIMIT 1");
    q.bindValue(":n",name);
    q.exec();
    if (q.next())
    {
        ret->id=q.value(0).toInt();
        ret->name=name;
        ret->show=q.value(1).toInt();
        ret->title=q.value(2).toString();
    }
    return *ret;
}

ProbModel &ProbModel::FindByID(int id)
{
    QSqlQuery q;
    ProbModel * ret=new ProbModel();
    q.prepare("SELECT name,show,title FROM problem WHERE id=:id LIMIT 1");
    q.bindValue(":id",id);
    q.exec();
    if (q.next())
    {
        ret->id=id;
        ret->name=q.value(0).toString();
        ret->show=q.value(1).toInt();
        ret->title=q.value(2).toString();
    }
    return *ret;
}

bool ProbModel::Save()
{
    QSqlQuery q;
    if (id != 0)
    {
        q.prepare("UPDATE problem SET name =:n ,show = :s,title = :t WHERE id = :i");
        q.bindValue(":i",id);
    }
    else
        q.prepare("INSERT INTO problem (name,show,title) VALUES (:n,:s,:t)");
    q.bindValue(":n",name);
    q.bindValue(":s",show);
    q.bindValue(":t",title);
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

QList<QStringList> ProbModel::GetList(int page, int item)
{
    QList<QStringList> ret;
    QSqlQuery q;
    q.prepare("SELECT name,title FROM problem LIMIT :item OFFSET :page");
    q.bindValue(":item",item);
    q.bindValue(":page",(page-1)*item);
    q.exec();
    while (q.next())
    {
        QStringList tmp;
        tmp.push_back(q.value(0).toString());
        tmp.push_back(q.value(1).toString());
        ret.push_back(tmp);
    }
    return ret;
}
