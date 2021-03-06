/**
  @file
  @author Stefan Frings
*/

#include "static.h"
#include "startup.h"
#include "dualfilelogger.h"
#include "httplistener.h"
#include "requestmapper.h"
#include "staticfilecontroller.h"
#include "templateloader.h"
#include "model/db.h"
#include "model/probmodel.h"
#include "model/usermodel.h"
#include "model/submitmodel.h"
#include "controller/judgecontroller.h"
#include <QDir>

/** Name of this application */
#define APPNAME "SQOJ"

/** Publisher of this application */
#define ORGANISATION "yuzeming@gmail.com"

/** Short description of this application */
#define DESCRIPTION "StarQoQ Online Judge"

/** The HTTP listener of the application */
HttpListener* listener;

void Startup::start() {
    // Initialize the core application
    QCoreApplication* app = application();
    app->setApplicationName(APPNAME);
    app->setOrganizationName(ORGANISATION);
    QString configFileName=Static::getConfigDir()+"/"+QCoreApplication::applicationName()+".ini";

    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    templateSettings->beginGroup("templates");
    Static::templateLoader=new TemplateLoader(templateSettings,app);

    //Disable for debug
    // Configure logging
    /*
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    logSettings->beginGroup("logging");
    Logger* logger=new FileLogger(logSettings,10000,app);
    logger->installMsgHandler();
    */
    // Configure session store
    QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    sessionSettings->beginGroup("sessions");
    Static::sessionStore=new HttpSessionStore(sessionSettings,app);

    // Configure static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    fileSettings->beginGroup("docroot");
    Static::staticFileController=new StaticFileController(fileSettings,app);

    // Configure and start the TCP listener
    qDebug("ServiceHelper: Starting service");
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    listenerSettings->beginGroup("listener");
    listener=new HttpListener(listenerSettings,new RequestMapper(app),app);

    // Configure and  start the db Driver
    qDebug("DB : Starting service");
    QSettings * dbSettings = new QSettings(configFileName,QSettings::IniFormat,app);
    dbSettings->beginGroup("db");
    Static::db = new ModelBase(dbSettings,app);

    qDebug("HTML : Read Prob Root");
    QSettings * HTMLSettings = new QSettings(configFileName,QSettings::IniFormat,app);
    HTMLSettings->beginGroup("prob");
    ProbModel::ProbRoot = HTMLSettings->value("probRoot","./prob").toString();

    qDebug("Data : Read Data Root");
    QSettings * DataSettings = new QSettings(configFileName,QSettings::IniFormat,app);
    DataSettings->beginGroup("prob");
    JudgeController::DataRoot = DataSettings->value("dataRoot","./data").toString();
    JudgeController::JudgeKey = DataSettings->value("judgeKey","").toString();

    /*if (logSettings->value("bufferSize",0).toInt()>0 && logSettings->value("minLevel",0).toInt()>0) {
        qDebug("You see these debug messages because the logging buffer is enabled");
    }*/

    ProbModel a;

    qWarning("ServiceHelper: Service has started");
}

void Startup::stop() {
    // Note that the stop method is not called when you terminate the application abnormally
    // by pressing Ctrl-C or when you kill it by the task manager of your operating system.

    // Deleting the listener here is optionally because QCoreApplication does it already.
    // However, QCoreApplication closes the logger at first, so we would not see the shutdown
    // debug messages, without the following line of code:
    delete listener;

    qWarning("ServiceHelper: Service has been stopped");
}


Startup::Startup(int argc, char *argv[])
    : QtService<QCoreApplication>(argc, argv, APPNAME)
{
    setServiceDescription(DESCRIPTION);
    //setStartupType(AutoStartup);
}



