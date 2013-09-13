#ifndef PROBMODEL_H
#define PROBMODEL_H
#include <QObject>
#include <QDir>
#include "db.h"

class ProbModel :public ModelBase
{
    Q_OBJECT
public:
    static QDir ProbRoot;
    QString name;
    QString title;
    int id;
    int show;

    QString readHTML();
    QString readConf();

    ProbModel(QString _name=QString(), QString _title=QString(), int _show=1);
    ProbModel(const ProbModel &copy);
    bool Save();

    static QList<QStringList> GetList(int page = 1,int item=30);
    static ProbModel &Find(QString name);
    static ProbModel &FindByID(int id);
};

#endif // PROBMODEL_H
