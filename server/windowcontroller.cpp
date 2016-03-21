#include "windowcontroller.h"

#include "optionwindows.h"
#include "serverwindows.h"

#include <QDebug>
#include <QApplication>

WindowController::WindowController(QObject *parent) : QObject(parent),
    config(new QSettings("config.ini", QSettings::IniFormat)),
    opt(new OptionWindows()),
    serv(new ServerWindows(config))
{
    connect(opt, SIGNAL(done()), this, SLOT(startServer()));
}

WindowController::~WindowController()
{
    if(opt != NULL)  delete opt;
    if(serv != NULL) delete serv;

    delete config;
}

void WindowController::load()
{
    QStringList options = QString("port autohost scriptfolder").split(" ");
    bool containsAll = true;

    foreach(QString option, options){
        if(!config->contains(option)){
            containsAll = false;
        }
    }

    if(containsAll && config->value("autohost").toBool()){
        this->startServer();
    }else{
        this->openOptions();
    }
}

void WindowController::startServer()
{
    serv->show();
}

void WindowController::openOptions()
{
    opt->show();
}

void WindowController::windowsClosed(QMainWindow *windows)
{
    if(windows == opt){
        opt = NULL;
    }else if(windows == serv){
        serv = NULL;
    }
}
