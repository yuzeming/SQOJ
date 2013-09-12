#include "submitcontroller.h"
#include <QVector>
#include <QJsonDocument>
#include "controller/probcontroller.h"
#include "model/probmodel.h"
#include "templateloader.h"
SubmitController::SubmitController()
{
}

QByteArray State[]={
    QByteArray("Waiting"),
    QByteArray("Running"),
    QByteArray("Accepted"),
    QByteArray("Wrong answer"),
    QByteArray("Runtime error"),
    QByteArray("Time limit exceeded"),
    QByteArray("Memory limit exceeded"),
    QByteArray("Compilation error")
};

void SubmitController::show(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    int sid = GetLastDir(request.getPath()).toInt();
    SubmitModel sm = SubmitModel::FindByID(sid);
    if (sm.id == 0) return response.Error404();
    UserModel um = UserModel::FindByID(sm.uid);
    ProbModel pm = ProbModel::FindByID(sm.pid);
    TemplateDictionary dict("template");
    dict.SetIntValue("SID",sid);
    dict.SetValue("SRC",sm.src.data());
    dict.SetValue("RES",sm.res.toStdString().c_str());
    dict.SetValue("USER",um.username.toStdString().c_str());
    dict.SetValue("PROB",pm.name.toStdString().c_str());
    if (sm.state == 0)
        dict.SetValue("STATE",State[sm.state].data());
    return response.write(Static::templateLoader->Render(dict,"submit_show",session));
}

void SubmitController::list(HttpRequest &request, HttpResponse &response)
{

}

void SubmitController::service(HttpRequest &request, HttpResponse &response)
{
    if (request.getPath().startsWith("/submit/show/"))
        return show(request,response);
    else if (request.getPath().startsWith("/submit/list/"))
        return list(request,response);
    return response.Error404();

}
