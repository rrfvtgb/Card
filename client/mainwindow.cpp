#include "mainwindow.h"

#include <ui/serverlist.h>
#include <ui/menu.h>
#include <ui/gamewidget.h>
#include <ui/option.h>

#include <QStackedWidget>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QSettings>

#include <control/game.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _view( new QStackedWidget),
    _menu( new Menu),
    _list( new ServerList),
    _game( new GameWidget),
    _option( new Option),

    _instance(NULL),
    _msgBox(NULL)
{
    this->setView(MenuUi);

    this->setCentralWidget(_view);

    connect(_menu, SIGNAL(play()), this, SLOT(showServerList()) );
    connect(_menu, SIGNAL(option()), this, SLOT(showOption()));
    connect(_menu, SIGNAL(exit()), this, SLOT(close()) );

    connect(_list, SIGNAL(exit()), this, SLOT(showMenu()));
    connect(_list, SIGNAL(join(QString,int,QString)), this, SLOT(connectTo(QString,int,QString)));

    connect(_option, SIGNAL(done()), this, SLOT(showMenu()));


    QSettings settings("config.ini", QSettings::IniFormat);

    if(settings.contains("geometry")){
        this->restoreGeometry(settings.value("geometry").toByteArray());
    }
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
    case OptionUi:
        this->setView(_option);
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

void MainWindow::showOption()
{
    this->setView(OptionUi);
}

void MainWindow::connectTo(QString address, int gamemode, QString deckname)
{
    if(_instance != NULL){
        delete _instance;
    }

    if(_msgBox != NULL){
        _msgBox->deleteLater();
    }

    this->setView(GameUi);

    _msgBox = new QMessageBox(this);
    _msgBox->setText(tr("Connecting..."));
    _msgBox->setStandardButtons(QMessageBox::Cancel);
    _msgBox->show();

    _instance = new Game(address, this);
    _instance->setWidget(_game);

    switch(gamemode){
    case 1:
        _instance->setMode(Game::DeckBuilder);
        break;
    case 2:
        _instance->setMode(Game::Spectator);
        break;
    case 0:
    default:
        _instance->setMode(Game::Normal);
        break;
    }

    connect(_instance, SIGNAL(closed(QString)), this, SLOT(disconnected(QString)));
    connect(_instance, SIGNAL(connected()), this, SLOT(connected()));

    connect(_msgBox, SIGNAL(finished(int)), this, SLOT(cancelConnection(int)));
}

void MainWindow::cancelConnection(int)
{
    if(_msgBox != NULL){
        _msgBox->deleteLater();
        _msgBox = NULL;
    }

    if(_instance != NULL){
        _instance->deleteLater();
        _instance = NULL;
    }

    this->showServerList();
}

void MainWindow::connected()
{
    if(_msgBox != NULL){
        _msgBox->hide();
        _msgBox->deleteLater();
        _msgBox = NULL;
    }
}

void MainWindow::disconnected(QString reason)
{
    if(_msgBox != NULL){
        _msgBox->setText(reason);
    }else{
        _msgBox = new QMessageBox(this);
        _msgBox->setText(reason);
        this->cancelConnection(_msgBox->exec());
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("geometry", saveGeometry());
    QWidget::closeEvent(event);
}
