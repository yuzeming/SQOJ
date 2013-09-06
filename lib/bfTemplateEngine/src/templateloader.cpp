/**
  @file
  @author Stefan Frings
*/

#include "templateloader.h"
#include <QFile>
#include <QFileInfo>
#include <QStringList>
#include <QDir>
#include <QSet>
#include "httprequest.h"
#include "httpresponse.h"
#include "httpsession.h"
#include <string>

TemplateLoader::TemplateLoader(QSettings* settings, QObject* parent)
    : QObject(parent)
{
    templatePath=settings->value("path",".").toString();
    BaseRender = NULL;
    // Convert relative path to absolute, based on the directory of the config file.
#ifdef Q_OS_WIN32
    if (QDir::isRelativePath(templatePath) && settings->format()!=QSettings::NativeFormat)
#else
    if (QDir::isRelativePath(templatePath))
#endif
    {
        QFileInfo configFile(settings->fileName());
        templatePath=QFileInfo(configFile.absolutePath(),templatePath).absoluteFilePath();
    }
    fileNameSuffix=settings->value("suffix",".tpl").toString();
    QString encoding=settings->value("encoding").toString();
    if (encoding.isEmpty()) {
        textCodec=QTextCodec::codecForLocale();
    }
    else {
       textCodec=QTextCodec::codecForName(encoding.toLocal8Bit());
   }
   qDebug("TemplateLoader: path=%s, codec=%s",qPrintable(templatePath),textCodec->name().data());
}

TemplateLoader::~TemplateLoader() {}

QString TemplateLoader::tryFile(QString localizedName) {
    QString fileName=templatePath+"/"+localizedName+fileNameSuffix;
    qDebug("TemplateCache: trying file %s",qPrintable(fileName));
    QFile file(fileName);
    if (file.exists())
        return fileName;
    return "";
}


QByteArray TemplateLoader::Render(TemplateDictionary &dict, QString localizedName,HttpSession &session)
{
    QString f = tryFile(localizedName);
    if (f=="")  return "";
    std::string output;
    ExpandTemplate(f.toStdString(),DO_NOT_STRIP,&dict,&output);
    if (BaseRender)
        return BaseRender(QByteArray(output.c_str()),dict,session);
    return QByteArray(output.c_str());
}
