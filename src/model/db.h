#ifndef DB_H
#define DB_H

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QObject>
#include <QSettings>

class ModelBase: public QObject
{
    Q_OBJECT
//    Q_DISABLE_COPY(ModelBase)
public:
    ModelBase(QSettings* settings=0, QObject* parent=0);
    ModelBase(const ModelBase & copy);
    static QSqlDatabase db;
    static QString dbname;
    virtual bool Save();
    int GetLastRowID(QSqlQuery &q);
};

#endif // DB_H

