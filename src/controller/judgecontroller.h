#ifndef JUDGECONTROLLER_H
#define JUDGECONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "templateloader.h"
#include <QDir>

class JudgeController: public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(JudgeController)
public:
    JudgeController();
    static QDir DataRoot;
    static QString JudgeKey;
    void GetSrc(HttpRequest &request, HttpResponse &response);
    void GetData(HttpRequest &request, HttpResponse &response);
    void SubmitTask(HttpRequest &request, HttpResponse &response);
    void GetTask(HttpRequest &request, HttpResponse &response);
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // JUDGECONTROLLER_H
