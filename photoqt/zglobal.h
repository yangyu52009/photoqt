#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QDir>
/*公共头文件*/
#include "zlogger.h"
            /* 全局使用的配置信息*/
#define VERSION "0.1"
#define APP_NAME "photoqt"
#define APP_DEF "PhotoQt Image Viewer"


const QString CONFIG_DIR = QString ("%1/.config/PhotoQt").arg ( QDir::homePath ());
const QString DATA_DIR = QString ("%1/.local/share/PhotoQt/").arg ( QDir::homePath ());
const QString CACHE_DIR = QString ("%1/.cache/PhotoQt/").arg ( QDir::homePath ());

const QString CFG_SETTINGS_FILE = QString ("%1/settings").arg ( CONFIG_DIR);
const QString CFG_CONTEXTMENU_FILE = QString ("%1/contextmenu").arg ( CONFIG_DIR);
const QString CFG_FILEFORMATS_FILE = QString ("%1/fileformats.disabled").arg ( CONFIG_DIR);
const QString CFG_KEY_SHORTCUTS_FILE = QString("%1/shortcuts").arg( CONFIG_DIR);
const QString CFG_TOUCH_SHORTCUTS_FILE = QString("%1/touchshortcuts").arg( CONFIG_DIR);
const QString CFG_MOUSE_SHORTCUTS_FILE = QString("%1/mouseshortcuts").arg( CONFIG_DIR);
const QString CFG_SHORTCUTSNOTIFIER_FILE = QString("%1/shortcutsnotifier").arg( CONFIG_DIR);
const QString CFG_THUMBNAILS_DB	 = QString("%1/thumbnails").arg( CACHE_DIR);
const QString CFG_SETTINGS_SESSION_FILE = QString("%1/settings_session").arg( CACHE_DIR);
const QString CFG_MAINWINDOW_GEOMETRY_FILE = QString("%1/geometry").arg( CONFIG_DIR);
const QString CFG_OPENFILE_LAST_LOCATION = QString("%1/openfilelastlocation").arg( CACHE_DIR);
const QString CFG_LASTOPENEDIMAGE_FILE = QString("%1/lastimageloaded").arg( CONFIG_DIR);
#endif // GLOBAL_H
