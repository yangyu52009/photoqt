#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QObject>
#include <QCommandLineParser>
/*!
* @version 0.1
* @anchor zl
* @note 20170909
* @def 解析传入的命令行参数，单例设计，实际就是对于 QCommandLineParser的使用
*/
class ZCommandLineParser : public QObject
{
    Q_OBJECT
public:
    QCommandLineParser parser;

    explicit ZCommandLineParser( QCoreApplication *app, QObject* parent = 0);


};

#endif // COMMANDLINEPARSER_H
