#ifndef PROBCONTROLLER_H
#define PROBCONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include "templateloader.h"

class ProbController : public HttpRequestHandler
{
    Q_OBJECT
    Q_DISABLE_COPY(ProbController)
public:
    explicit ProbController(QObject *parent = 0);
    void list(HttpRequest &request, HttpResponse &response);
    void show(HttpRequest &request, HttpResponse &response);
    void submit(HttpRequest &request, HttpResponse &response);
    void service(HttpRequest &request, HttpResponse &response);
signals:
    
public slots:
    
};

#endif // PROBCONTROLLER_H
