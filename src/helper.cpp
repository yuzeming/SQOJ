#include "helper.h"

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"


void Redirec(HttpResponse &response,QString go)
{
    response.setStatus(302);
    response.setHeader("Location",go);
}
