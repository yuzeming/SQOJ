#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include "db.h"
class UserModel :public ModelBase
{
    Q_OBJECT
public:
    QString username;
    QString password;
    int isAdmin;
    int id;
    UserModel(QString u=QString(),QString p=QString(),int a=0);
    bool Save();
    static UserModel &AuthUser(QString u,QString p);
};

#endif // USERMODEL_H
