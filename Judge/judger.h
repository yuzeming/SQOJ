#ifndef JUDGER_H
#define JUDGER_H

#include <QObject>
#include <QDir>
#include <QJsonArray>
#include <QSettings>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkCookieJar>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
class Judger : public QObject
{
    Q_OBJECT
public:
    static QDir SrcRoot;
    static QDir DataRoot;
    static QDir TmpDir;
    static QString Server;
    static QString JudgeKey;
    static QVariantMap CompConf;
    QNetworkAccessManager myManager;
    explicit Judger(QSettings *settings = NULL, QObject *parent = 0);

    QByteArray Get(QString path);

    QByteArray GetTask();
    bool GetData(QString name,QString writeto);
    QByteArray GetSrc(int sid);
    bool SubmitTask(int sid,QJsonDocument res);

    bool Unzip(QString zip,QDir to);

    bool Complie(QString Src, QString Exe, QString lang, QString &Res);
    bool Run(QString Exe, QString lang, const QStringList &Conf, QStringList &Res);
    double Diff(QString cmp,QString input,QString stdout, QString output, QString &Res);

    void exec();

signals:
    
public slots:
    
};

#endif // JUDGER_H
