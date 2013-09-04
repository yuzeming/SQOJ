#include "usercontroller.h"
#include "../static.h"
UserController::UserController()
{
}

int UserController::Auth(QString username, QString password)
{
    return 1;
}

void UserController::login(HttpRequest &request, HttpResponse &response)
{
    QString user=request.getParameter("username");
    QString pass=request.getParameter("password");
    QByteArray go = request.getParameter("go");
    if (go=="" || go == request.getPath())
        go="/";
    int UID=Auth(user,pass);
    HttpSession session=Static::sessionStore->getSession(request,response);
    if (UID>0)
    {
        session.set("userid",UID);
        return response.Redirec(go);
    }
    return ;

}


void UserController::service(HttpRequest &request, HttpResponse &response)
{
}
