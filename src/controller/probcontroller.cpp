#include "probcontroller.h"
#include "model/probmodel.h"
#include <QStringList>
#include "usercontroller.h"
#include "templateloader.h"
#include "../static.h"
#include <iostream>
#include "model/submitmodel.h"
#include <QDir>

ProbController::ProbController(QObject *parent) :
    HttpRequestHandler(parent)
{
}

QString GetLastDir(QString path)
{
    return QDir(path).dirName();
}


void ProbController::list(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    int page = GetLastDir(request.getPath()).toInt();
    if (page==0) page = 1;
    QStringList list = ProbModel::GetList(page);
    TemplateDictionary dict("template");
    for (int i=0;i<list.size();++i)
    {
        TemplateDictionary * tmp = dict.AddSectionDictionary("PROB_LIST");
        tmp->SetValue("PORB_NAME",list[i].toStdString());
    }
    return response.write(Static::templateLoader->Render(dict,"problist",session));
}

void ProbController::show(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    QString name = GetLastDir(request.getPath());
    ProbModel prob = ProbModel::Find(name);
    if (prob.id==0) return response.Error404();
    TemplateDictionary dict("template");
    dict.SetValue("PROB_NAME",name.toStdString());
    dict.SetValue("PROB_CONTENT",prob.readHTML().toStdString());
    return response.write(Static::templateLoader->Render(dict,"probshow",session));
}

void ProbController::submit(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    int uid=session.get("USER_ID").toInt();
    if (uid == 0)
        return response.Redirec("/user/login?go="+request.getPath());
    QString name = GetLastDir(request.getPath());
    ProbModel prob = ProbModel::Find(name);
    if (prob.id==0) return response.Error404();
    if (request.getMethod()=="POST")
    {
        QByteArray src = request.getParameter("src");
        QString lang = request.getParameter("lang");
        SubmitModel sb(prob.id,uid,src,lang);
        sb.Save();
        return response.Redirec("/submit/show/"+QByteArray::number(sb.id));
    }
    TemplateDictionary dict("template");
    dict.SetValue("PROB_NAME",name.toStdString());
    return response.write(Static::templateLoader->Render(dict,"submit",session));
}


void ProbController::service(HttpRequest &request, HttpResponse &response)
{
    if (request.getPath()=="/problem/"||request.getPath().startsWith("/problem/list/"))
        return list(request,response);
    if (request.getPath().startsWith("/problem/submit/"))
        return submit(request,response);
    if (request.getPath().startsWith("/problem/show/"))
        return show(request,response);
    return response.Error404();
}
