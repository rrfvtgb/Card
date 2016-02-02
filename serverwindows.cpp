#include "serverwindows.h"
#include "ui_serverwindows.h"

#include "clientsocket.h"

#include <QSettings>
#include <QTcpServer>

ServerWindows::ServerWindows(QWidget *parent):
    ServerWindows(new QSettings("config.ini", QSettings::IniFormat),
                  parent)
{

}

ServerWindows::ServerWindows(QSettings *conf, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::ServerWindows),
    config(conf)
{
    ui->setupUi(this);
}

ServerWindows::~ServerWindows()
{
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

    loaded = server->listen(QHostAddress::Any, config->value("port").toInt());

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

void ServerWindows::on_input_chat_returnPressed()
{

}
