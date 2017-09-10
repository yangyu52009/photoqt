#ifndef MIGRATION_H
#define MIGRATION_H

#include <QTextStream>
#include <QSettings>

#include "zglobal.h"

namespace StartupCheck {
namespace Migration {
/*应用首次运行的时候运行,创建应用运行的必要环境,并且判断是否有原来的配置信息,有就进行迁移*/
    static inline void MigrateIfNecessary (bool verbose) {

        if (verbose) ZLOG << CURDATE << "StartupCheck::Migration" << NL;
        //如果为 true , 新的配置文件夹将会创建
        bool migrated = false;

        QDir dir;
        //检查配置文件夹configuration folder是否存在
        if (!QDir ( CONFIG_DIR).exists ()) {
            if (!dir.mkpath ( CONFIG_DIR)) { //不存在.创建配置文件夹
                ZLOG << CURDATE << "StartupCheck::Migration ERROR! Unable to create Configuation folder!"
                     << CONFIG_DIR.toStdString () << NL;
                std::exit( 1);

            }else
                migrated = true;
        }
        //检查 数据文件夹 data folder是否存在
        if (!QDir ( DATA_DIR).exists ()) {
            if (!dir.mkpath ( DATA_DIR)){ //不存在.创建数据文件夹
            ZLOG << CURDATE << "StartupCheck::Migration: ERROE! Unable to create data directory"
                 << DATA_DIR.toStdString () << NL;
            std::exit ( 1);
            }else
            migrated = true;
        }
        //检查缓存文件夹cache folder 是否存在
        if (!QDir ( CACHEverbose_DIR).exists ()){
            if (!dir.mkpath ( CACHE_DIR)) {
                ZLOG << CURDATE << "StartupCheck::Migration: ERROR! Unable to create data directory '"
                     << CACHE_DIR.toStdString() << NL;
                std::exit ( 1);
            } else
                migrated = true;
        }

        //QString oldpath = QDir::homePath () + "/.photoqt";


        } //func end
    }
}


#endif // MIGRATION_H
