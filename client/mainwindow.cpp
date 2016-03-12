#include "mainwindow.h"

#include <ui/serverlist.h>
#include <ui/menu.h>
#include <ui/gamewidget.h>

#include <QStackedWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _view( new QStackedWidget),
    _menu( new Menu),
    _list( new ServerList),
    _game( new GameWidget)
{
    this->setView(MenuUi);
    this->setBaseSize(640, 480);

    this->setCentralWidget(_view);

    connect(_menu, SIGNAL(play()), this, SLOT(showServerList()) );
    connect(_menu, SIGNAL(exit()), this, SLOT(close()) );

    connect(_list, SIGNAL(exit()), this, SLOT(showMenu()));
    connect(_list, SIGNAL(join(QString)), this, SLOT(connectTo(QString)));
}

void MainWindow::setView(MainWindow::Ui type)
{
    switch(type){
    case MenuUi:
        this->setView(_menu);
        break;
    case ServerListUi:
        this->setView(_list);
        break;
    case GameUi:
        this->setView(_game);
        break;
    }
}

void MainWindow::setView(QWidget *widget)
{
    int index = _view->indexOf(widget);

    if(index != -1){
        _view->setCurrentIndex(index);
    }else{
        _view->setCurrentIndex(
                    _view->addWidget(widget));
    }
}

void MainWindow::showMenu()
{
    this->setView(MenuUi);
}

void MainWindow::showServerList()
{
    this->setView(ServerListUi);
}

void MainWindow::connectTo(QString address)
{
    qDebug() << "connecting to" << address ;
}
