#ifndef SUBMITCONTROLLER_H
#define SUBMITCONTROLLER_H
#include "usercontroller.h"
#include "templateloader.h"
#include "../static.h"
#include <iostream>
#include "model/usermodel.h"
#include "model/submitmodel.h"

class SubmitController : public HttpRequestHandler
{
public:
    SubmitController();
    void show(HttpRequest &request, HttpResponse &response);
    void list(HttpRequest &request, HttpResponse &response);
    void setRes(HttpRequest &request, HttpResponse &response);
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // SUBMITCONTROLLER_H
