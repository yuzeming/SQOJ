/**
  @file
  @author Stefan Frings
*/

#ifndef STATIC_H
#define STATIC_H

#include <QString>
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "templateloader.h"
#include "model/db.h"

/**
  This class contains some static resources that are used by the application.
*/

class Static
{
public:

    /**
      Search the main config file and return its full path.
      On the first call, the INI file gets searched. If not found,
      the application aborts with an error message.
      <p>
      The filename is the applications name plus the ending ".ini". It is searched
      in the following directories:

      - Same directory as the applications executable file
      - In ../etc relative to the applications executable file
      - In ../../etc relative to the applications executable file
      - In /etc/xdg/{organisation name} on the root drive
      - In /etc/opt on the root drive
      - In /etc on the root drive

     */
    static QString getConfigFileName();

    /**
      Gets the directory where the main config file is located.
      On the first call, the INI file gets searched. If not found,
      the application aborts with an error message.
      @see getConfigFileName()
     */
    static QString getConfigDir();
    static QString getTemplateDir();

    /** Storage for session cookies */
    static HttpSessionStore* sessionStore;

    /** Controller for static files */
    static StaticFileController* staticFileController;

    static TemplateLoader* templateLoader;

    static ModelBase * db;

private:

    /** Directory of the main config file */
    static QString configDir;
    static QString templateDir;

};

#endif // STATIC_H
