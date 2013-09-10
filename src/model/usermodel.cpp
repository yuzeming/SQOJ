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
        query.exec("CREATE TABLE user ("
                           "id INTEGER PRIMARY KEY,"
                           "username varchar(20) UNIQUE NOT NULL PRIMARY KEY,"
                           "password varchar(20) NOT NULL ,"
                           "isadmin int DEFAULT 0"
                           ") ");
        //TODO : debug
        UserModel("yzm","a",1).Save();
    }
    username = u;
    password = p;
    isAdmin = a;
    id = 0;
}

bool UserModel::Save()
{
    QSqlQuery q;
    if (id != 0)
    {
        q.prepare("UPDATA user SET username =:u ,password = :p ,isadmin = :a WHERE id = :i");
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
    query.prepare("SELECT id,passowrd,isadmin FROM user WHERE username=:u LIMIT 1");
    query.bindValue(":u",u);
    query.exec();
    UserModel * ret = new UserModel();
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

