#include "db.h"
#include <QSqlDatabase>

QSqlDatabase ModelBase::db = QSqlDatabase();
QString ModelBase::dbname = QString();

ModelBase::ModelBase(QSettings *settings, QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    dbname = settings->value("dbname","sqoj.db").toString();
    db.setDatabaseName(dbname);
}


bool ModelBase::Save()
{
    return false;
}
