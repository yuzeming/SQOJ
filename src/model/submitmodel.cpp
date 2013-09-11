#include "submitmodel.h"
#include "db.h"
#include <QSqlQuery>
#include <QStringList>
#include <QVector>
SubmitModel::SubmitModel(int _pid, int _uid, QByteArray _src,QString _lang, int _state, QString _res,QString _compRes) : ModelBase()
{
    QSqlQuery query;
    QStringList tabls=db.tables();
    if (tabls.count("submit")==0)
    {
        bool res=query.exec("CREATE TABLE submit ("
                           "id INTEGER PRIMARY KEY,"
                            "state INTEGER DEFAULT 0,"
                           "uid INTEGER NOT NULL,"
                           "pid INTEGER NOT NULL,"
                            "lang TEXT,"
                            "src BLOB,"
                            "res BLOB,"
                            "compRes BLOB"
                           ") ");
        Q_ASSERT(res);
    }
    pid=_pid;
    uid=_uid;
    state=_state;
    src=_src;
    res=_res;
    compRes=_compRes;
    lang=_lang;
    id = 0;
}

SubmitModel::SubmitModel(const SubmitModel &copy) : ModelBase()
{
    pid=copy.pid;
    uid=copy.uid;
    state=copy.state;
    src=copy.src;
    res=copy.res;
    compRes=copy.compRes;
    id = copy.id;
    lang=copy.lang;
}

bool SubmitModel::Save()
{
    QSqlQuery q;
    if (id != 0)
    {
        q.prepare("UPDATA submit SET pid =:pid ,uid = :uid ,state=:state,src=:src,res=:res,compRes=:compRes lang=:lang WHERE id = :i");
        q.bindValue(":i",id);
    }
    else
        q.prepare("INSERT INTO submit (pid,uid,state,src,res,compRes,lang) VALUES (:pid,:uid,:state,:src,:res,:compRes,:lang)");
    q.bindValue(":pid",pid);
    q.bindValue(":uid",uid);
    q.bindValue(":state",state);
    q.bindValue(":src",src);
    q.bindValue(":res",res);
    q.bindValue(":compRes",compRes);
    q.bindValue(":lang",lang);
    bool ret= q.exec();
    if (id==0)
        id = GetLastRowID(q);
    return ret;
}

SubmitModel &SubmitModel::FindByID(int id)
{
    QSqlQuery query;
    SubmitModel * ret = new SubmitModel();
    query.prepare("SELECT pid,uid,state,src,res,compRes,lang FROM submit WHERE id=:id LIMIT 1");
    query.bindValue(":id",id);
    query.exec();
    if (query.next())
    {
        ret->id = id;
        ret->pid = query.value(0).toInt();
        ret->uid = query.value(1).toInt();
        ret->state = query.value(2).toInt();
        ret->src = query.value(3).toByteArray();
        ret->res = query.value(4).toString();
        ret->compRes = query.value(5).toString();
        ret->lang = query.value(6).toString();
    }
    return *ret;
}

QVector<int> SubmitModel::GetIDByState(int state,int limit)
{
    QSqlQuery q;
    q.prepare("SELECT id FROM submit WHERE state=:state LIMIT :limit");
    q.bindValue(":state",state);
    q.bindValue(":limit",limit);
    QVector<int> ret;
    while (q.next())
        ret.push_back(q.value(0).toInt());
    return ret;
}
