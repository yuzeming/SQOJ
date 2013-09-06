#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class UserController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(UserController)
public:
    UserController();
    int Auth(QString username,QString password);
    void login(HttpRequest& request, HttpResponse& response);
    void logout(HttpRequest& request, HttpResponse& response);
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // USERCONTROLLER_H
