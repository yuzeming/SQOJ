#include "usercontroller.h"
#include "templateloader.h"
#include "../static.h"
#include <iostream>
#include "model/usermodel.h"
UserController::UserController()
{
}

int UserController::Auth(QString username, QString password)
{
    UserModel tmp=UserModel::AuthUser(username,password);
    return tmp.id;
}

void UserController::login(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    QByteArray go = request.getParameter("go");

    if (request.getMethod()=="POST")
    {
        QString user=request.getParameter("username");
        QString pass=request.getParameter("password");
        int UID=Auth(user,pass);
        if (UID>0)
        {
            session.set("USER_ID",UID);
            session.set("USER_NAME",user);
            go = session.get("go").toByteArray();
            if (go=="" || go == request.getPath())
                go="/";
            session.remove("go");
            return response.Redirec(go);
        }
    }
    session.set("go",go);
    TemplateDictionary dict("userlogin");
    dict.SetValueAndShowSection("error","login failed","error_div");
    return response.write(Static::templateLoader->Render(dict,"login",session));
}

void UserController::logout(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    QByteArray go = request.getParameter("go");
    if (go=="" || go == request.getPath())
        go="/";
    session.remove("USER_ID");
    session.remove("USER_NAME");
    return response.Redirec(go);
}


void UserController::service(HttpRequest &request, HttpResponse &response)
{
    if (request.getPath().startsWith("/user/login"))
        return login(request,response);
    if (request.getPath().startsWith("/user/logout"))
        return logout(request,response);
    return response.Error404();
}

