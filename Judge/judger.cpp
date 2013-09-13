#include "judger.h"
#include <QJsonObject>
#include <QProcess>
#include <cstdio>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <dirent.h>

QDir Judger::SrcRoot = QDir();
QDir Judger::DataRoot = QDir();
QDir Judger::TmpDir = QDir();
QString Judger::Server = QString();
QString Judger::JudgeKey = QString();
QVariantMap Judger::CompConf = QVariantMap();

Judger::Judger(QSettings* settings, QObject *parent) :
    QObject(parent) , myManager(parent)
{
    if (settings !=NULL)
    {
        SrcRoot = settings->value("srcRoot","./src").toString();
        DataRoot = settings->value("dataRoot","./data").toString();
        TmpDir = settings->value("tmpDir","./tmp").toString();
        Server = settings->value("server","http://127.0.0.1:8080").toString();
        JudgeKey = settings->value("judgeKey","").toString();
        QString compjson=settings->value("complierConf","./compiler.json").toString();
        QFile jsonf(compjson);
        Q_ASSERT (jsonf.open(QIODevice::ReadOnly));
        QJsonDocument doc ;
        doc.fromBinaryData(jsonf.readAll());
        jsonf.close();
        Q_ASSERT (doc.isObject());
        QJsonObject obj = doc.object();
        CompConf=obj.toVariantMap();
    }
}

QByteArray Judger::Get(QString path)
{
    QNetworkRequest http;
    QByteArray ret;
    http.setUrl(Server+path+JudgeKey);
    QNetworkReply * Reply=myManager.get(http);
    if (Reply->error()==QNetworkReply::NoError)
        ret=Reply->readAll();
    delete Reply;
    return ret;
}

QByteArray Judger::GetTask()
{
    return Get("/judge/gettask");
}

bool Judger::GetData(QString name, QString writeto)
{
    QNetworkRequest http;
    QString path = "/judge/getdata/%1/";
    path.arg(name);
    http.setUrl(Server+path+JudgeKey);
    QNetworkReply * Reply=myManager.get(http);
    QFile fwrite(writeto);
    bool ret = false;
    if (Reply->error()==QNetworkReply::NoError && fwrite.open(QIODevice::WriteOnly))
    {
        while (!Reply->atEnd())
            fwrite.write(Reply->read(65535));
        fwrite.close();
        ret = true;
    }
    delete Reply;
    return ret;
}

QByteArray Judger::GetSrc(int sid)
{
    return Get(QString("/judge/getsrc/%1/").arg(sid));
}

bool Judger::SubmitTask(int sid, QJsonDocument res)
{
    QNetworkRequest http;
    QString path = "/judge/submittask/%1/";
    path.arg(sid);
    QByteArray json=res.toBinaryData();
    http.setUrl(Server+path+JudgeKey);
    http.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply * Reply=myManager.post(http,json.toPercentEncoding());
    bool ret=Reply->readAll() == "OK";
    delete Reply;
    return ret;
}

bool Judger::Unzip(QString zip, QDir to)
{
    QStringList args;
    args.push_back(zip);
    args.push_back("-d");
    args.push_back(to.absolutePath());
    return QProcess::execute("unzip",args)==0;
}

#define __CTE 10	// 10S		最长编译时限
#define __CRE (128*1024*1024) //128M	最大占用内存

bool Judger::Complie(QString Src, QString Exe, QString lang, QString &Res)
{
    int St;
    QStringList args = CompConf[lang].toList()[0].toString().split(" ");
    args.replaceInStrings("%SRC%",Src);
    args.replaceInStrings("%EXE%",Exe);
    char **pargs = new char *[args.size()+1];
    for (int i=0;i<args.size();++i)
    {
        pargs[i]=new char [args[i].size()+1];
        strncpy(pargs[i],args[i].toStdString().c_str(),args[i].size()+1);
    }
    pargs[args.size()+1]=NULL;
    if (int CpPID=fork())
    {	//父进程
        if (CpPID==-1)
        {
            Res="无法创建子进程";
            return false;
        }
        wait(&St);
        QFile flog(TmpDir.filePath("Complie.log"));
        flog.open(QIODevice::ReadOnly);
        Res=flog.readAll();
        flog.close();
        flog.remove();
        for (int i=0;i<args.size();++i)
            delete pargs[i];
        delete pargs;
        return St==0;
    }
    else
    {
        //子进程
        int tmp=creat("Complie.log",S_IRWXO|S_IRWXG|S_IRWXU);
        dup2(tmp,STDOUT_FILENO);
        dup2(tmp,STDERR_FILENO);
        struct rlimit CPU_R;
        CPU_R.rlim_cur=__CTE;
        CPU_R.rlim_max=__CTE+1;
        setrlimit(RLIMIT_CPU,&CPU_R);
        struct rlimit RAM_R;
        RAM_R.rlim_cur=__CRE;
        RAM_R.rlim_max=__CRE+1024*1024;
        setrlimit(RLIMIT_AS,&RAM_R);
        execvp(pargs[0],pargs);
        exit(-1);
    }
}

bool Judger::Run(QString Exe,QString lang, const QStringList &Conf, QStringList &Res)
{
    QStringList args = CompConf[lang].toList()[1].toString().split(" ");
    args.replaceInStrings("%EXE%",Exe);
    char **pargs = new char *[args.size()+1];
    for (int i=0;i<args.size();++i)
    {
        pargs[i]=new char [args[i].size()+1];
        strncpy(pargs[i],args[i].toStdString().c_str(),args[i].size()+1);
    }
    pargs[args.size()+1]=NULL;

    QString inputfile = Conf[0];
    QString outputfile = Conf[1];
    int MaxTime=Conf[2].toInt();
    int MaxRAM=Conf[3].toInt();
    int RAMUsed,TimeUsed,ExeRet;
    QString sRes;
    if (int RPID=fork())
    {
        int State;
        struct rusage Use;
        wait4(RPID,&State,WUNTRACED,&Use);
        ExeRet=State;
        RAMUsed=int(Use.ru_minflt/1024.0*sysconf(_SC_PAGESIZE));
        TimeUsed=Use.ru_utime.tv_sec*1000+Use.ru_utime.tv_usec/1000
                +Use.ru_stime.tv_sec*1000+Use.ru_stime.tv_usec/1000;
        switch(State)
        {
            case SIGKILL:		//超出内存限制 会被判这个
                sRes="程序被终止";
                break;
            case SIGSEGV:
                sRes="非法访问";
                break;
            case SIGFPE:
                sRes="被零除";
                break;
            case SIGSTKFLT:
                sRes="堆栈溢出";
                break;
            case SIGXCPU:
                sRes="超时";
                break;
            case 0:
                //正常
                break;
            default :
                sRes="未知错误";;
                break;
        }
        Res.push_back(QString::number(ExeRet));
        Res.push_back(QString::number(RAMUsed));
        Res.push_back(QString::number(TimeUsed));
        Res.push_back(sRes);
        return true;
    }
    else
    {
        int tmpin=open(inputfile.toStdString().c_str(),O_RDONLY);
        dup2(tmpin,STDIN_FILENO);
        int tmpout=creat(outputfile.toStdString().c_str(),S_IRWXO|S_IRWXG|S_IRWXU);
        dup2(tmpout,STDERR_FILENO);
        struct rlimit CPU_R;
        CPU_R.rlim_cur=MaxTime;
        CPU_R.rlim_max=MaxTime+1;
        setrlimit(RLIMIT_CPU,&CPU_R);
        struct rlimit RAM_R;
        RAM_R.rlim_cur=MaxRAM*1024;
        RAM_R.rlim_max=MaxRAM*1024+1024*1024;
        setrlimit(RLIMIT_AS,&RAM_R);
        chdir(TmpDir.absolutePath().toStdString().c_str());
        execvp(pargs[0],pargs);
        exit(-1);
    }
}

double Judger::Diff(QString cmp,QString input,QString stdout, QString output, QString &Res)
{
    if (fork())
    {
        wait(NULL);
        QFile flog(TmpDir.filePath("judge.log"));
        flog.open(QIODevice::ReadOnly);
        QString Res=flog.readAll();
        QStringList list=Res.split(" ",QString::SkipEmptyParts);
        flog.close();
        flog.remove();
        Res=list[1];
        return list[0].toDouble();
    }
    else
    {
        int tmp=creat("judge.log",S_IRWXO|S_IRWXG|S_IRWXU);
        dup2(tmp,STDOUT_FILENO);
        execl(cmp.toStdString().c_str(),
              cmp.toStdString().c_str(),
              input.toStdString().c_str(),
              output.toStdString().c_str(),
              stdout.toStdString().c_str(),
              (char *)NULL
              );
        exit(-1);
    }
}

void Judger::exec()
{
    QJsonObject taskjson;
    while (true)
    {
        QByteArray rawTask=GetTask();
        QJsonDocument doc;
        doc.fromBinaryData(rawTask);
        if (!doc.isNull())
        {
            taskjson=doc.object();
            break;
        }
    }
    QString sid=taskjson["id"].toString();
    QString lang=taskjson["lang"].toString();
    QString pname=taskjson["pname"].toString();

    //Save Src
    QByteArray srcdata;
    srcdata = GetSrc(sid.toInt());
    QFile srcfile(SrcRoot.filePath(sid+"."+lang));
    srcfile.open(QIODevice::WriteOnly);
    srcfile.write(srcdata);
    srcfile.close();

    //Data
    if (!DataRoot.exists(pname))
    {   //downland
        DataRoot.mkdir(pname);


    }
    QFile datafile();

}




