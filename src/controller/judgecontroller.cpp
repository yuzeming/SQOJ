#include "judgecontroller.h"
#include "model/submitmodel.h"
#include "controller/probcontroller.h"
#include "model/probmodel.h"
#include <QJsonDocument>

QDir JudgeController::DataRoot=QDir();
QString JudgeController::JudgeKey=QString();

JudgeController::JudgeController()
{
}

void JudgeController::GetSrc(HttpRequest &request, HttpResponse &response)
{
    int sid = GetLastDir(request.getPath()).toInt();
    if (sid==0) return response.Error404();
    SubmitModel sm = SubmitModel::FindByID(sid);
    return response.write(sm.src);
}

void JudgeController::GetData(HttpRequest &request, HttpResponse &response)
{
    int pid = GetLastDir(request.getPath()).toInt();
    ProbModel pm = ProbModel::FindByID(pid);
    if (pm.id==0)   return response.Error404();
    QFile f(DataRoot.filePath(pm.name+".zip"));
    return response.SendFile(f);
}

void JudgeController::GetTask(HttpRequest &request, HttpResponse &response)
{
    QVector<int> id = SubmitModel::GetID(-1,-1,0,1);
    QJsonDocument doc;
    if (id.size()==1)
    {
        SubmitModel sm=SubmitModel::FindByID(id[0]);
        QJsonObject obj;
        obj["id"]=sm.id;
        obj["pid"]=sm.pid;
        obj["lang"]=sm.lang;
        sm.state = 2;
        sm.Save();
        doc.setObject(obj);
    }
    return response.write(doc.toJson().data());
}

void JudgeController::service(HttpRequest &request, HttpResponse &response)
{
    if (request.getParameter("KEY")!=JudgeKey)
        return response.setStatus(401);
    if (request.getPath().startsWith("/judge/gettask"))
        return GetTask(request,response);
    else if (request.getPath().startsWith("/judge/getsrc"))
        return GetSrc(request,response);
    else if (request.getPath().startsWith("/judge/getdata"))
        return GetData(request,response);
}
