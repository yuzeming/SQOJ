/**
  @file
  @author Stefan Frings
*/

#include "static.h"
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QString>

QString Static::configDir=0;

HttpSessionStore* Static::sessionStore=0;

StaticFileController* Static::staticFileController=0;

TemplateLoader* Static::templateLoader=0;

ModelBase* Static::db=0;

QString Static::getConfigFileName() {
    return QString("%1/%2.ini").arg(getConfigDir()).arg(QCoreApplication::applicationName());
}

QString Static::getConfigDir() {
    if (!configDir.isNull()) {
        return configDir;
    }
    // Search config file

    QString binDir=QCoreApplication::applicationDirPath();
    QString organization=QCoreApplication::organizationName();
    QString configFileName=QCoreApplication::applicationName()+".ini";

    QStringList searchList;
    searchList.append(QDir::cleanPath(binDir));
    searchList.append(QDir::cleanPath(binDir+"/../etc"));
    searchList.append(QDir::cleanPath(binDir+"/../../etc")); // for development under windows
    searchList.append(QDir::rootPath()+"etc/xdg/"+organization);
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");
    searchList.append(QDir::currentPath());
    // TODO: TEST ONLY!!
    searchList.append("/home/yzm/SQOJ/etc");

    foreach (QString dir, searchList) {
        QFile file(dir+"/"+configFileName);
        if (file.exists()) {
            // found
            configDir=dir;
            qDebug("Using config file %s",qPrintable(file.fileName()));
            return configDir;
        }
    }

    // not found
    foreach (QString dir, searchList) {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(configFileName));
    }
    qFatal("Cannot find config file %s",qPrintable(configFileName));
    return 0;
}

