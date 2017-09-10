#include "zcommandlineparser.h"
#include "zglobal.h"
ZCommandLineParser::ZCommandLineParser(QCoreApplication *app, QObject* parent )//parent = 0
    : QObject(parent)
{
    //当前仅仅支持long option
    this->parser.setSingleDashWordOptionMode ( QCommandLineParser::ParseAsLongOptions);
    //设置标准选项
    this->parser.setApplicationDescription ( APP_DEF );
    this->parser.addHelpOption ();
    this->parser.addVersionOption ();

    //添加自定义选项
    QList <QCommandLineOption > list;
    QCommandLineOption opt_open ( QStringList() << "o" << "open", tr ("Make PhotoQt ask for a new File"));
    list.append ( opt_open);
    QCommandLineOption opt_toggle ( QStringList() << "t" << "toggle", tr ("Toggle PhotoQt - hides PhotoQt if visible, shows if hidden"));
    list.append ( opt_toggle);
    QCommandLineOption opt_show ( QStringList() << "s" << "show", tr("shows PhotoQt"));
    list.append ( opt_show);
    QCommandLineOption opt_hide ( QStringList() << "h" << "hide", tr("hides PhotoQt"));
    list.append ( opt_hide);
    QCommandLineOption opt_nothumbs ( "no-thumbs", tr ("Disable thumbbails"));
    list.append ( opt_nothumbs);
    QCommandLineOption opt_thumbs ( "thumbs", tr ("Enable thumbnails"));
    list.append ( opt_thumbs);
    QCommandLineOption opt_startintray ( "Start-in-tray", tr ("Start PhotoQt hideden to System (at start-up only)"));
    list.append ( opt_startintray);
    QCommandLineOption opt_verbose ( QStringList () << "debug" << "verbose", tr ("Enable debug message (at start-up only)"));
    list.append ( opt_verbose);
    this->parser.addOptions ( list);
    // Add optional argument 'filename'
    this->parser.addPositionalArgument ( "Filename", tr ("File to open with PhotoQt"), "[filename]");

    this->parser.process ( *app);
}

