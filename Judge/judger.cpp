#include "judger.h"

QDir Judger::SrcRoot = QDir();
QDir Judger::DataRoot = QDir();
QDir Judger::TmpDir = QDir();
QUrl Judger::Server = QUrl();
QString Judger::JudgeKey = QString();

Judger::Judger(QObject *parent) :
    QObject(parent)
{
}
