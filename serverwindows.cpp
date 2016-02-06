#include "serverwindows.h"
#include "ui_serverwindows.h"

#include "broadcastsocket.h"
#include "clientsocket.h"
#include "gameengine.h"

#include <QSettings>
#include <QTcpServer>

#include <network/packet01message.h>
#include <network/packetmanager.h>

ServerWindows::ServerWindows(QWidget *parent):
    ServerWindows(new QSettings("config.ini", QSettings::IniFormat),
                  parent)
{
}

ServerWindows::ServerWindows(QSettings *conf, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::ServerWindows),
    _config(conf),
    _broadcast(new BroadcastSocket(this)),
    game(new GameEngine(this))
{
    ui->setupUi(this);
    server   = new QTcpServer(this);
    _loaded = false;
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
    client->setName(tr("Player-%1").arg(clientID));
    client->setServer(this);

    ui->statusbar->showMessage(tr("Connected client: %1").arg(clients.size()));

    clientID ++;

    this->sendMessage(tr("A new player joined the game"),"");
}

void ServerWindows::showEvent(QShowEvent *)
{
    if(_loaded) return;

    clientID = 0;

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    _loaded = server->listen(QHostAddress::Any, _config->value("port").toInt());

    if(!_loaded){
        qDebug() << "Can't start the server, exiting now...";
        this->close();
    }else{
        ui->statusbar->showMessage("Server ready!");
    }
}

void ServerWindows::closeEvent(QCloseEvent *)
{
    emit closed(this);
}

QHash<int, ClientSocket*> ServerWindows::getClients() const
{
    return clients;
}

void ServerWindows::sendMessage(const QString &playername, const QString &message)
{
    Packet01Message* m = dynamic_cast<Packet01Message*>
            (PacketManager::getPacket(0x01));

    m->bytesToWrite(_broadcast, playername, message);

    ui->text_chat->appendHtml("<b style='color:#6a6;'>&lt;"+playername.toHtmlEscaped()+"&gt;</b> "+message.toHtmlEscaped());
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
    this->sendMessage("Server", ui->input_chat->text());
    ui->input_chat->setText("");
}
