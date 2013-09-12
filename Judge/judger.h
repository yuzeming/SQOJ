#ifndef JUDGER_H
#define JUDGER_H

#include <QObject>
#include <QDir>
#include <QJsonArray>
#include <QSettings>

class Judger : public QObject
{
    Q_OBJECT
public:
    static QDir SrcRoot;
    static QDir DataRoot;
    static QDir TmpDir;
    static QUrl Server;
    static QString JudgeKey;

    explicit Judger(QSettings *settings = NULL, QObject *parent = 0);

    QByteArray GetTask();
    bool GetData(QString name);
    bool GetSrc(int sid);
    bool SubmitTask(QJsonDocument);

    bool Unzip(QFile zip,QDir to);

    bool Complie(QString Src,QString Exe,QByteArray &Res);
    bool Run(QString Exe,const QJsonArray& Conf,QJsonArray& Res);
    double Diff(QJsonArray& Conf,QString output,QString& Res);

    void Init();
    void exec();

signals:
    
public slots:
    
};

#endif // JUDGER_H
