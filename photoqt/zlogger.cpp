#include "zlogger.h"
#include <sstream>

#include <QDateTime>
#include <QTextStream>
ZLogger::ZLogger()
{
   if (QFile( CONFIG_DIR + QString ("/verboselog")).exists ()) {
       m_logFile.setFileName ( QDir::tempPath () + "/photoQt.log");
       this->m_writeToFile = true;
   }else {
       this->m_writeToFile = false;
   }
}

ZLogger& ZLogger::operator>>(std::ostream &(*f)(std::ostream &))
{
    std::clog << f;
    return *this;
}

//template<class T>
//ZLogger &ZLogger::operator<<(const ZLogger::T &v)
//{
//    std::stringstream str;
//    str << v;

//    if (str.str () == "[[[DATE]]]")
//        std::clog << "["
//                  << QDateTime::currentDateTime ().
//                     toString ("dd/MM/yyyy HH:mm:ss:zzz").
//                     toStdString () << "]";
//    else
//        std::clog << v;


//    if ( this->m_writeToFile) {

//        QTextStream out ( &m_logFile);
//        //使用只写和最佳模式打开文件
//        this->m_logFile.open ( QIODevice::WriteOnly | QIODevice::Append);
//        if (str.str () == "[[[DATE]]]")
//            out << "[" << QDateTime::currentDateTime ().
//                   toString ("dd/MM/yyyy HH:mm:ss:zzz") << "]";
//        else
//            out << QString::fromStdString ( str.str ());

//        this->m_logFile.close ();
//    }
//    return *this;
//}

