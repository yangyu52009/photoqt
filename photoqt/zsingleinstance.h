#ifndef ZSINGLEINSTANCE_H
#define ZSINGLEINSTANCE_H

#include <QApplication>
#include <QLocalServer>
#include <QLocalSocket>

/*!
* @version 0.1
* @anchor zl
* @note 20170910
* @def 1.这个类实现应用程序单例
*      2. 将应用的其它实例启动时候将其启动的参数 转发到 单例，关闭程序
*      3. 解析传递的参数(ZCommandLineParser类中实现)，并将结果使用信号发送
* @note 基本编译检查 ok 运行逻辑检查 !ok
*/
class ZSingleInstance : public QApplication
{
    Q_OBJECT
public:
    explicit ZSingleInstance( int&, char*[]);
    ~ZSingleInstance ();


    //记录了传递来的信息,各个字段的含义可以参考 ZCommandLineParser 类的注释
    bool open;
    bool nothumbs;
    bool thumbs;
    bool toggle;
    bool show;
    bool hide;

    bool verbose;
    bool startintray;
    QString filename;

    // DEVELOPMENT ONLY
    bool update;
    bool install;
signals:
    void interaction ( QString exec); //发送解析的参数，关联的槽函数将处理 执行
private slots:
    //这个槽函数被调用时说明一个新的应用程序实例运行
    void newConnection(); //该槽函数与 QLocalServer 对象的 newConnection关联
private:
    QLocalServer * m_server;//仅仅在第一个运行的应用中使用，用于接受来自于其它该应用进程所转发的信息（状态或是参数信息）
    QLocalSocket * m_socket;

private:
    //这个函数处理命令行解析之后的内容，该内容可能来源于当前进程启动时传递的参数 或是
    //运行另一个程序实例时候，它发送而来的信息
    void handleResponse (QString msg);
};

#endif // ZSINGLEINSTANCE_H
