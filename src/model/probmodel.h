#ifndef PROBMODEL_H
#define PROBMODEL_H
#include <QObject>
#include "db.h"

class ProbModel :public ModelBase
{
public:
    static QString HTMLDIR;
    QString name;
    int id;
    int show;
    QString readHTML();
    QString readConf();
    ProbModel(QString _name=QString(),int _show=1);
    static ProbModel &Find(QString name);
    bool Save();
};

#endif // PROBMODEL_H
