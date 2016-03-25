#include "windowcontroller.h"

#ifndef SERVER_CONSOLE
# include "optionwindows.h"

# include <QApplication>
#endif

#include "serverwindows.h"

#include <QDebug>

WindowController::WindowController(QObject *parent) : QObject(parent),
    config(new QSettings("config.ini", QSettings::IniFormat)),
    serv(new ServerWindows(config))
{
#ifndef SERVER_CONSOLE
    opt = new OptionWindows();
    connect(opt, SIGNAL(done()), this, SLOT(startServer()));
#endif
}

WindowController::~WindowController()
{
#ifndef SERVER_CONSOLE
    if(opt != NULL)  delete opt;
#endif

    if(serv != NULL) delete serv;

    delete config;
}

void WindowController::load()
{
    QStringList options = QString("port autohost scriptfolder").split(" ");
#ifndef SERVER_CONSOLE
    bool containsAll = true;
#endif

    foreach(QString option, options){
        if(!config->contains(option)){
#ifndef SERVER_CONSOLE
            containsAll = false;
#else
            QTextStream s(stdin);
            QTextStream ts( stdout );

            ts << option << "? ";
            QString value = s.readLine();

            config->setValue(option, value);
#endif
        }
    }

#ifndef SERVER_CONSOLE
    if(containsAll && config->value("autohost").toBool()){
        this->startServer();
    }else{
        this->openOptions();
    }
#else
    this->startServer();
#endif
}

void WindowController::startServer()
{
#ifndef SERVER_CONSOLE
    serv->show();
#endif

    serv->load();
}

void WindowController::openOptions()
{
#ifndef SERVER_CONSOLE
    opt->show();
#endif
}

#ifndef SERVER_CONSOLE
void WindowController::windowsClosed(QMainWindow *windows)
{
    if(windows == opt){
        opt = NULL;
    }else if(windows == serv){
        serv = NULL;
    }
}
#endif
