#include "serverwindows.h"
#include "ui_serverwindows.h"

#include "clientsocket.h"
#include "gameengine.h"

#include <QSettings>
#include <QTcpServer>

ServerWindows::ServerWindows(QWidget *parent):
    ServerWindows(new QSettings("config.ini", QSettings::IniFormat),
                  parent)
{

}

ServerWindows::ServerWindows(QSettings *conf, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::ServerWindows),
    _config(conf),
    game(new GameEngine(this))
{
    ui->setupUi(this);
}

ServerWindows::~ServerWindows()
{
    delete game;
    delete server;
    delete ui;
}

void ServerWindows::broadcast(const QByteArray &data)
{
    foreach(ClientSocket* client, clients){
        client->write(data);
    }
}

void ServerWindows::newConnection()
{
    ClientSocket* client = new ClientSocket(server->nextPendingConnection());

    clients[clientID] = client;
    client->setId(clientID);
    client->setServer(this);

    ui->statusbar->showMessage("Connected client: " + clients.size());

    clientID ++;
}

void ServerWindows::showEvent(QShowEvent *)
{
    bool loaded;

    server   = new QTcpServer(this);
    clientID = 0;

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    loaded = server->listen(QHostAddress::Any, _config->value("port").toInt());

    if(!loaded){
        qDebug() << "Can't start the server, closing... \0";
        this->close();
    }else{
        ui->statusbar->showMessage("Server ready!");
    }
}

void ServerWindows::closeEvent(QCloseEvent *)
{
    emit closed(this);
}

QSettings *ServerWindows::config() const
{
    return _config;
}

void ServerWindows::setConfig(QSettings *config)
{
    _config = config;
}

void ServerWindows::on_input_chat_returnPressed()
{
    
}
