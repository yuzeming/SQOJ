#include "indexpage.h"

void IndexPage(HttpRequest &request, HttpResponse &response)
{
    HttpSession session=Static::sessionStore->getSession(request,response);
    TemplateDictionary dict("template");
    return response.write(Static::templateLoader->Render(dict,"index",session));
}
