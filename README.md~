SQOJ by Yuzeming
====
SQOJ sTARq Online Judge (With Qt)

#程序架构

程序有两部分组成
1. Web 前端 提供Web界面，组织竞赛题目，用户管理，接受用户提交，显示评测结果等主要功能。
2. Judge 评测端 从Web端下载评测数据，用户代码，在本地编译并测试，向Web前端提交评测结果。

## Web 前端
Web前端基于QtWebApp编写。 重写了QtWebApp的小部分代码。

其中bfTemplateLoader完全移除，使用Google CTemplate 代替。编写部分功能 以适应模版扩展。

数据库使用了SQLite（通过QtSQL进行了连接）。

整体采用MVC架构。

部分功能由于时间原因被裁剪。

依赖于 Qt5 ,Google Ctemplate.在编译前需要先安装。

# 许可证信息
程序使用GPL v2 许可证
Google CTemplate 使用New BSD License许可，从这里code.google.com/p/ctemplate/‎ 可以获得源代码。
QtWebApp 使用LGPL许可，从这里 http://stefanfrings.de/qtwebapp/index-en.html 可以获得源代码。

#Web端 

##代码说明

###src目录
包含了大部分Cpp代码。
#### controller 控制器部分

每个文件都实现了一个类。类中的service虚函数提供了URL分发。其他成员函数提供实际的功能

* indexpage.cpp/h 首页

* judgecontroller.cpp/h 后端通信
    与Judge通信，Judge需要提供JudgeKey以验证身份，防止代码，测试数据等泄露。

   * void GetSrc(HttpRequest &request, HttpResponse &response);
    获得提交的源代码
   * void GetData(HttpRequest &request, HttpResponse &response);
    获得测试数据压缩包
   * void SubmitTask(HttpRequest &request, HttpResponse &response);
    提交测试结果
   * void GetTask(HttpRequest &request, HttpResponse &response);
    获得一条待评测的记录
   ToDo
   1. 分辨不同评测端
   2. 提供数据包Hash，以便在数据包更新以后，向评测端更新数据包
   
* probcontroller.cpp/h 所有题目显示。列表。

  *  void list(HttpRequest &request, HttpResponse &response);
    显示题目列表
  *  void show(HttpRequest &request, HttpResponse &response);
    显示题目
  *  void submit(HttpRequest &request, HttpResponse &response);
    提交代码并保存
  
  ToDo
  1. 添加题目（目前的题目是手工添加的）
  2. 删除题目
  3. 隐藏题目（仅当管理员用户登陆时显示所有题目，以保证添加竞赛题目时保密）
  
* submitcontroller.cpp/h 提交代码显示。列表。

  * void show(HttpRequest &request, HttpResponse &response);
    显示提交代码结果
  * void list(HttpRequest &request, HttpResponse &response);
    显示提交列表
  
  ToDo
  1. 重新评测 （以便修正数据错误）
  2. 实时返回评测结果

* usercontroller.cpp/h 用户登陆。用户管理。

  * int Auth(QString username,QString password);
    认证用户函数，返回0 或者用户ID
  * void login(HttpRequest& request, HttpResponse& response);
    登陆
  * void logout(HttpRequest& request, HttpResponse& response);
    登出
  
  ToDo
  1. 用户注册
  2. 用户禁用
  3. 显示用户通过的题目排名

#### model 模型部分

模型部分提供 Class 与 SQL Talbe 的相互映射，并提供了一些额外的数据借口，用于读取磁盘上的数据。

* db.h 提供了基础SQL 链接支持。
  * ModelBase(QSettings* settings=0, QObject* parent=0);
    构造，setting可以传入SQL连接配置。
  * ModelBase(const ModelBase & copy);
    拷贝函数
  * static QSqlDatabase db;
    数据库链接
  * static QString dbname;
    数据库名
  * virtual bool Save();
    虚函数，保存模型
  * int GetLastRowID(QSqlQuery &q);
    获得最后插入行的ID

* probmodel.h/cpp 题目模型
  * static QDir ProbRoot;
    保存题目内容文件的根目录
  * QString name;
    题目名称（短名称，唯一）
  * QString title;
    题目名称（长名称，用于显示）
  * int id;
    SQL 主键ID
  * int show;
    是否显示

  * QString readHTML();
    读取题目内容HTML
  * QString readConf();
    读取题目配置，用于读取配置的的时间/内存限制
    
  * ProbModel(QString _name=QString(), QString _title=QString(), int _show=1);
    构造函数
  * ProbModel(const ProbModel &copy);
    拷贝函数
  * bool Save();
    保存/更新 模型到数据库。

  * static QList<QStringList> GetList(int page = 1,int item=30);
    返回列表
  * static ProbModel &Find(QString name);
  * static ProbModel &FindByID(int id);
    提供了查找制定记录并返回模型结构。

* submitmodel.cpp/h 提交记录模型
  * int id;
    SQL 主键ID
  * int pid;
    所属题目ID
  * int uid;
    由UID用户提交
  * int state;
    评测状态
  * QByteArray src;
    源代码
  * QString res;
    返回结果 （Json格式）
  * QString compRes;
    编译返回
  * QString lang;
    所用语言（C++/Java ... ）
  * SubmitModel(int _pid=0,int _uid=0,QByteArray _src=QByteArray(),QString _lang=QString(),int _state=0,QString _res=QString(),QString _compRes = QString());
  
  * SubmitModel(const SubmitModel &copy);
  
  * bool Save();
  
  * static SubmitModel &FindByID(int id);
  
  * static QVector<int> GetID(int uid=-1,int pid=-1,int state=-1,int limit=30);
  返回列表

* usermodel.cpp/h
  * QString username;
    用户名
  * QString password;
    密码
  * int isAdmin;
    是否为管理员
  * int id;
    主键

  * UserModel(QString u=QString(),QString p=QString(),int a=0);
  * UserModel(const UserModel& copy);
  * bool Save();

  * static UserModel &AuthUser(QString u,QString p);
    认证函数
  * static UserModel &FindByID(int id);
  
  ToDO
  1. HASH 保存密码

### 其他部分

* requestmapper.cpp / h
    总Http请求分发

* startup.h/cpp
    读取配置文件

* static.h
    全局变量保存

## etc 目录
    保存配置文件 ，静态文件

###docroot
    静态文件

###templates
    Ctemplate 模板保存于此
    
###SQOJ.ini
    全局主要配置文件

##lib 底层库文件
来自QtWebApp

###bfHttpServer
    http，请求解析，返回响应

###bfLogging
    日志
    
###bfTemplateEngine
    模板引擎，移除原有代码，基于Ctemplate重新实现。

###qtservice
    将自身注册为服务（Win) 或者 daemon (Unix) 提供后台运行能力

## logs 日志文件
    日志文件由于调试需要被禁用

## prob 题目描述 HTML 格式
    子目录名为 Prob.Name (短名称）
    子目录下有inde.html 保存题目描述
    
    ToDo
    1. 添加图片插入/文件附加支持

## sqoj.db
    数据库文件


# Judge 评测端 
Judge 评测端，运行与Linux环境下，支持多种语言编译。
一个Web前端可以拥有多个评测端以加快评测速度。

调用G++/OpenJDK/Python等编译器进行编译

## 代码说明
* judger.h.cpp
  * static QDir SrcRoot;
  * static QDir DataRoot;
  * static QDir TmpDir;
  * static QString Server;
  * static QString JudgeKey;
  * static QVariantMap CompConf;
    读取的配置信息
    
  * explicit Judger(QSettings *settings = NULL, QObject *parent = 0);
    构造函数，从settings中读取配置信息

  * QByteArray GetTask();
    从服务器上获得一条记录
  * bool GetData(QString name,QString writeto);
    下载数据文件
  * QByteArray GetSrc(int sid);
    下载源代码
  * bool SubmitTask(int sid,QJsonDocument res);
    提交评测结果

  * bool Unzip(QString zip,QDir to);
    解压缩

  * bool Complie(QString Src, QString Exe, QString lang, QString &Res);
    编译代码
  * bool Run(QString Exe, QString lang, const QStringList &Conf, QStringList &Res);
    运行可执行文件
  * double Diff(QString cmp,QString input,QString stdout, QString output, QString &Res);
    比较输出
    

  * void exec();

http://github.com/yuzeming/SQOJ

