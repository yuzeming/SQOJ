#include "usercontroller.h"
#include "templateloader.h"
#include "../static.h"
#include <iostream>
UserController::UserController()
{
}

int UserController::Auth(QString username, QString password)
{
    return username=="yzm"&&password=="a";
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
        session.set("user",user);
        return response.Redirec(go);
    }
    TemplateDictionary dict("userlogin");
    dict.SetValueAndShowSection("error","login failed","error_div");
    return response.write(Static::templateLoader->Render(dict,"login",session));
}


void UserController::service(HttpRequest &request, HttpResponse &response)
{
    if (request.getPath().startsWith("/user/login"))
        return login(request,response);
    return response.Error404();
}
