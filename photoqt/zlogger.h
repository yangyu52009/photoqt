#ifndef ZLOGGER_H
#define ZLOGGER_H

#include <iostream>
#include <sstream>
#include <QFile>
#include <QString>
#include <QDir>
#include <QTextStream>
#include <QDateTime>

#include "zglobal.h"

#define ZLOG ZLogger ()
const std::string CURDATE = "[[[DATE]]]";
const std::string NL = "\n";


class ZLogger
{
public:
    ZLogger();

    template<class T>
    ZLogger &operator<< (const T &v)
    {
        std::stringstream str;
        str << v;

        if (str.str () == "[[[DATE]]]")
            std::clog << "["
                      << QDateTime::currentDateTime ().
                         toString ("dd/MM/yyyy HH:mm:ss:zzz").
                         toStdString () << "]";
        else
            std::clog << v;


        if ( this->m_writeToFile) {

            QTextStream out ( &m_logFile);
            //使用只写和最佳模式打开文件
            this->m_logFile.open ( QIODevice::WriteOnly | QIODevice::Append);
            if (str.str () == "[[[DATE]]]")
                out << "[" << QDateTime::currentDateTime ().
                       toString ("dd/MM/yyyy HH:mm:ss:zzz") << "]";
            else
                out << QString::fromStdString ( str.str ());

            this->m_logFile.close ();
        }
        return *this;
    }

    ZLogger& operator>> (std::ostream& (*f)(std::ostream&));


private:
    QFile m_logFile;
    bool m_writeToFile;
};


//class Logger {

//public:
//    Logger() {
//        if(QFile(CONFIG_DIR + QString("/verboselog")).exists()) {
//            logFile.setFileName(QDir::tempPath() + "/photoqt.log");
//            writeToFile = true;
//        } else
//            writeToFile = false;
//    }

//    template <class T>

//    Logger &operator<<(const T &v) {

//        std::stringstream str;
//        str << v;

//        if(str.str() == "[[[DATE]]]")
//            std::clog << "[" << QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss:zzz").toStdString() << "] ";
//        else
//            std::clog << v;

//        if(writeToFile) {

//            QTextStream out(&logFile);
//            logFile.open(QIODevice::WriteOnly | QIODevice::Append);
//            if(str.str() == "[[[DATE]]]")
//                out << "[" << QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss:zzz") << "] ";
//            else
//                out << QString::fromStdString(str.str());

//            logFile.close();
//        }

//        return *this;

//    }

//    Logger &operator<<(std::ostream&(*f)(std::ostream&)) {
//        std::clog << f;
//        return *this;
//    }

//private:
//    QFile logFile;
//    bool writeToFile;

//};

//#define LOG Logger()
//const std::string CURDATE = "[[[DATE]]]";
//const std::string NL = "\n";


#endif // ZLOGGER_H
