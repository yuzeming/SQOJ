#include "db.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
QSqlDatabase ModelBase::db = QSqlDatabase();
QString ModelBase::dbname = QString();

ModelBase::ModelBase(QSettings *settings, QObject *parent) : QObject(parent)
{
    if (settings)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        dbname = settings->value("dbname","./sqoj.db").toString();
        db.setDatabaseName(dbname);
        qDebug() <<"Use "<<dbname <<" DB";
        Q_ASSERT(db.open());
    }
}

ModelBase::ModelBase(const ModelBase & copy) :QObject(copy.parent())
{
}


bool ModelBase::Save()
{
    return false;
}

int ModelBase::GetLastRowID(QSqlQuery &q)
{
    q.exec("SELECT last_insert_rowid()");
    q.next();
    return q.value(0).toInt();
}
