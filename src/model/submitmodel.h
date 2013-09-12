#ifndef SUBMITMODEL_H
#define SUBMITMODEL_H
#include "db.h"
#include <QByteArray>
#include <QJsonObject>
#include <QVector>

class SubmitModel : public ModelBase
{
    Q_OBJECT
public:
    int id;
    int pid;
    int uid;
    int state;
    QByteArray src;
    QString res;
    QString compRes;
    QString lang;
    SubmitModel(int _pid=0,int _uid=0,QByteArray _src=QByteArray(),QString _lang=QString(),int _state=0,QString _res=QString(),QString _compRes = QString());
    SubmitModel(const SubmitModel &copy);
    bool Save();
    static SubmitModel &FindByID(int id);
    static QVector<int> GetID(int uid=-1,int pid=-1,int state=-1,int limit=30);
};

#endif // SUBMITMODEL_H
