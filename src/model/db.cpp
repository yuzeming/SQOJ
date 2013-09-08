#include "db.h"

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
