#ifndef DB_H
#define DB_H

#include "mongo/client/dbclient.h"

using namespace mongo;

class StaticDB
{
public:
   static mongo::DBClientConnection *c;
};

#endif // DB_H

