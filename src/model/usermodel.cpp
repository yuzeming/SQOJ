#include "usermodel.h"
#include "db.h"
#include <QStringList>

StaticDB db;

UserModel::UserModel()
{
    QStringList tables=db.db->tables();
    if (tables.count("user")==0)
    {   //Creator Table
        QSqlQuery qurey();
        qurey.exec("CREATE TABLE ( "
                   "id int NOT NULL PRIMARY KEY,"
                   "username varchar(20) NOT NULL UNIQUE,"
                   "password varchar(32) NOT NULL"
                   ")");
    }

}
