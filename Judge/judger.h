#ifndef JUDGER_H
#define JUDGER_H

#include <QObject>

class Judger : public QObject
{
    Q_OBJECT
public:
    explicit Judger(QObject *parent = 0);
    void SetDataDir(QDir data);
    void SetSrcFile(QFile src);
signals:
    
public slots:
    
};

#endif // JUDGER_H