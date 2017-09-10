#ifndef UPDATECHECK_H
#define UPDATECHECK_H
#include "zglobal.h"
namespace StartupCheck {
namespace UpdateCheck {
// 0 = nothing, 1 = update, 2 = install
/*!
* @version 0.1
* @anchor zl
* @note 20170910
* @def
*/
        static inline int checkForUpdateInstall (bool verbose, QString *settingsText){
            if ( verbose) ZLOG << CURDATE << "StartupCheck::UpdataCheck|" << NL;
            QString version = VERSION;
            if (*settingsText == "") { //没有配置settings文件
                if ( verbose) ZLOG << CURDATE << "PhotoQt newly installed! Creating empty settings file" << NL;
                *settingsText = "version=" + version + "\n";
                Settin
            }
        }
}
}
#endif // UPDATECHECK_H
