#ifndef JUDGER_H
#define JUDGER_H

#include <QObject>
#include <QDir>

class Judger : public QObject
{
    Q_OBJECT
public:
    static QDir SrcRoot;
    static QDir DataRoot;
    static QDir TmpDir;
    static QUrl Server;
    static QString JudgeKey;
    explicit Judger(QObject *parent = 0);
    QJsonDocument GetTask();
    bool GetData(QString name);
    bool GetSrc(int sid);
    bool Unzip(QFile zip,QDir to);

    bool Complie(QString Src,QString Exe,,QByteArray &Res);
    bool Run(QString Exe,)
signals:
    
public slots:
    
};

#endif // JUDGER_H
