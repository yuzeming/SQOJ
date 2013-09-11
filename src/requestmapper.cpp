/**
  @file
  @author Stefan Frings
*/

#include "requestmapper.h"
#include "static.h"
#include "staticfilecontroller.h"
#include "controller/dumpcontroller.h"
#include "controller/formcontroller.h"
#include "controller/fileuploadcontroller.h"
#include "controller/sessioncontroller.h"
#include "controller/usercontroller.h"
#include "controller/probcontroller.h"
#include <iostream>

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    Static::templateLoader->BaseRender = & (RequestMapper::BaseRender);
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());
    if (path.startsWith("/dump")) {
        DumpController().service(request, response);
    }

    else if (path.startsWith("/user")) {
        UserController().service(request, response);
    }

    else if (path.startsWith("/file")) {
        FileUploadController().service(request, response);
    }

    else if (path.startsWith("/session")) {
        SessionController().service(request, response);
    }
    else if (path.startsWith("/problem"))
    {
        ProbController().service(request,response);
    }
    // All other pathes are mapped to the static file controller.
    else {
        Static::staticFileController->service(request, response);
    }
    qDebug("RequestMapper: finished request");
}

QByteArray RequestMapper::BaseRender(QByteArray content, TemplateDictionary &dict, HttpSession &session)
{
    QString f = Static::templateLoader->tryFile("base");
    if (f=="") return content;

    dict.SetValue("TITLE","SQOJ");
    dict.SetValue("CONTENT",content.data());
    QMap<QByteArray,QVariant>  map=session.getAll();
    for (QMap<QByteArray,QVariant>::Iterator it=map.begin();it!=map.end();++it)
        dict.SetValue(("SESSION_"+it.key().toUpper()).data(),it.value().toByteArray().data());

    if (session.get("USER_ID").isNull())
        dict.ShowSection("LOGIN");
    else
        dict.ShowSection("LOGOUT");

    std::string output;
    ExpandTemplate(f.toStdString(),DO_NOT_STRIP,&dict,&output);
    return QByteArray(output.c_str());
}
