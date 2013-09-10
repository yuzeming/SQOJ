#ifndef PROBMODEL_H
#define PROBMODEL_H
#include <QObject>
#include "db.h"

class ProbModel :public ModelBase
{
    Q_OBJECT
public:
    static QString HTMLDIR;
    QString name;
    int id;
    int show;
    QString readHTML();
    QString readConf();
    QStringList GetList(int page = 1,int item=30);
    ProbModel(QString _name=QString(),int _show=1);
    static ProbModel &Find(QString name);
    bool Save();
};

#endif // PROBMODEL_H
