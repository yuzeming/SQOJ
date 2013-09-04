#include "usercontroller.h"
#include "../static.h"
#include "../helper.h"
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
    QString go = request.getParameter("go");
    if (go=="" || go == request.path)
        go="/";
    int UID=Auth(user,pass);
    HttpSession session=Static::sessionStore->getSession(request,response);
    if (UID>0)
    {
        session.set("userid",id);
        return Redirec(response,go);
    }

}
