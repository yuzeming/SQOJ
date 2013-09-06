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
    dict.SetValue("CONTENT",content.data());
    std::string output;
    ExpandTemplate(f.toStdString(),DO_NOT_STRIP,&dict,&output);
    return QByteArray(output.c_str());
}
