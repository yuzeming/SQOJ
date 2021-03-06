#include "db.h"
#include "usermodel.h"
#include <QStringList>
#include <QtSql/QSqlQuery>
UserModel::UserModel(QString u, QString p, int a) : ModelBase()
{
    QSqlQuery query;
    QStringList tabls=db.tables();
    if (tabls.count("user")==0)
    {
        bool res=query.exec("CREATE TABLE user ("
                           "id INTEGER PRIMARY KEY,"
                           "username varchar(20) UNIQUE NOT NULL,"
                           "password varchar(20) NOT NULL ,"
                           "isadmin INTEGER DEFAULT 0"
                           ") ");
        Q_ASSERT(res);
        //TODO : debug
        UserModel("yzm","a",1).Save();
    }
    username = u;
    password = p;
    isAdmin = a;
    id = 0;
}

UserModel::UserModel(const UserModel &copy) : ModelBase()
{
    username=copy.username;
    password=copy.password;
    id = copy.id;
    isAdmin = copy.isAdmin;
}

bool UserModel::Save()
{
    QSqlQuery q;
    if (id != 0)
    {
        q.prepare("UPDATE user SET username =:u ,password =:p ,isadmin =:a WHERE id =:i");
        q.bindValue(":i",id);
    }
    else
        q.prepare("INSERT INTO user (username,password,isadmin) VALUES (:u,:p,:a)");
    q.bindValue(":u",username);
    q.bindValue(":p",password);
    q.bindValue(":a",isAdmin);
    return q.exec();
}

UserModel& UserModel::AuthUser(QString u,QString p)
{
    QSqlQuery query;
    UserModel * ret = new UserModel();
    query.prepare("SELECT id,password,isadmin FROM user WHERE username=:u LIMIT 1");
    query.bindValue(":u",u);
    query.exec();
    if (query.next())
    {
        int id = query.value(0).toInt();
        int admin = query.value(2).toInt();
        QString ps = query.value(1).toString();
        if (ps==p)
        {
            ret->username = u;
            ret->password = p;
            ret->id = id;
            ret->isAdmin = admin;
        }
    }
    return *ret;
}

UserModel &UserModel::FindByID(int id)
{
    QSqlQuery query;
    UserModel * ret = new UserModel();
    query.prepare("SELECT username,password,isadmin FROM user WHERE id=:id LIMIT 1");
    query.bindValue(":id",id);
    query.exec();
    if (query.next())
    {
        ret->id = id;
        ret->username = query.value(0).toInt();
        ret->password = query.value(1).toString();
        ret->isAdmin = query.value(2).toInt();
    }
    return *ret;
}

