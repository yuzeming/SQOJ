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
    static QSqlDatabase db;
    static QString dbname;
    virtual bool Save();
};

#endif // DB_H

