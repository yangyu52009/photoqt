#include "zsingleinstance.h"
#include <thread>
#include <chrono>

#include <QFileInfo>

#include "zcommandlineparser.h"
//#include "zglobal.h"
#include "zlogger.h"
ZSingleInstance::ZSingleInstance(int &argc, char * argv[]):
    QApplication ( argc, argv)
{
    //解析命令行参数
    ZCommandLineParser handler (this);
    //message 我们发送给 运行的实例
    QByteArray message = "";
    //检查文件名
    QStringList positional = handler.parser.positionalArguments ();
    if ( positional.length () > 0) {
        message += ":-:-:" +
                QByteArray ("::file::") +
                QFileInfo( positional.at (0)).absoluteFilePath ();
    }
    //检查其他的选项
    QStringList options = handler.parser.optionNames (); //返回所有的选项
    foreach (QString opt, options)
        message += ":-:-:::" + opt.toUtf8 () + "::";

    /*****************/
    /* Server/Socket */
    /*****************/
    /*实现应用单例在启动一个之后，转发在启动时候说传递的参数，使用本地服务传递*/
    //创建服务器
    QString server_str = qApp->applicationName ();

    //connect to a Local Server (if available)
    this->m_socket = new QLocalSocket ();
    m_socket->connectToServer ( server_str);

    //如果成功了，那么实例已经运行
    //如果没有参数传递,我们添加“显示”
    if (m_socket->waitForConnected ( 1000)) {
        if (argc == 1 )
            message += ":-:-:::show::";

        //发送已经合成的信息字符串
        m_socket->write ( message);
        m_socket->flush ();

        ZLOG << CURDATE << "Running instance of PhotoQt detected" << NL;
        //程序退出代码
        //将当前的进程休眠100ms
        std::this_thread::sleep_for ( std::chrono::milliseconds(100));
        std::exit ( 0);

        //单例应用运行，没有其他的运行
    }else {
        this->m_server = new QLocalServer ();
        m_server->removeServer ( server_str);
        m_server->listen ( server_str);
        this->connect ( this->m_server, &QLocalServer::newConnection,
                        this, &ZSingleInstance::newConnection);

        this->handleResponse ( message); //处理来自启动时候的参数信息
    }

}

ZSingleInstance::~ZSingleInstance()
{
    this->m_server->close ();
    delete this->m_socket;
    delete this->m_server;
}

void ZSingleInstance::newConnection()
{
    QLocalSocket* socket = this->m_server->nextPendingConnection ();

    if ( socket->waitForBytesWritten ( 2000))
        this->handleResponse ( socket->readAll ());
    socket->close ();
    delete socket; //这个socket由Qt创建，不知道时候会销毁
}

void ZSingleInstance::handleResponse(QString msg)
{
    // Analyse what action(s) to take

    // These ones are passed on to the main process
    //这些是传递主要的一些信息
    this->open = ( msg.contains ("::open::") && !msg.contains ("::file::"));
    this->nothumbs = ( msg.contains ("::no-thumbs::") && !msg.contains ("::thumbs::"));
    this->thumbs = ( msg.contains ("::thumbs::"));
    this->toggle = ( msg.contains ("::toggle::") && !msg.contains ("::start-in-stray::"));
    this->show = ( msg.contains ("::show::") || !msg.contains ("::hide::") && !msg.contains ("::toggle::"));
    this->hide = (msg.contains("::hide::") && !msg.contains("::toggle::") && !msg.contains("::start-in-tray::"));

    //这些信息仅仅启动时候有用，没有就忽略
    this->verbose = ( msg.contains ( "::verbose") ||
                      msg.contains ("::debug::") ||
                      QFile ( QString (CONFIG_DIR) + "/verbaselog").exists ());
    this->startintray = ( msg.contains ("::start-in-sray"));
    // DEVELOPMENT ONLY
    this->update = (msg.contains("::update::"));
    this->install = (msg.contains("::install::"));

    //检查 filename
    if(msg.contains("::file::"))
        this->filename = msg.split("::file::").at(1).split(":-:-:").at(0);
    else
        this->filename = "";

    if(filename != "") emit interaction("::file::" + filename);
    if(open) emit interaction("open");
    if(nothumbs) emit interaction("nothumbs");
    if(thumbs) emit interaction("thumbs");
    if(toggle) emit interaction("toggle");
    if(show) emit interaction("show");
    if(hide) emit interaction("hide");
}
