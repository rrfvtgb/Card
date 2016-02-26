#include "serverwindows.h"
#include "ui_serverwindows.h"

#include "broadcastsocket.h"
#include "clientsocket.h"
#include "gameengine.h"

#include <QSettings>
#include <QTcpServer>
#include <QMutexLocker>

#include <network/packet.h>
#include <network/packetmanager.h>

#include <command/commandhelper.h>

ServerWindows::ServerWindows(QWidget *parent):
    ServerWindows(new QSettings("config.ini", QSettings::IniFormat),
                  parent)
{
}

ServerWindows::ServerWindows(QSettings *conf, QWidget *parent) : QMainWindow(parent),
    ui(new Ui::ServerWindows),
    _config(conf),
    _broadcast(new BroadcastSocket(this)),
    _lock(),
    _broadcastLock(),
    _command(new CommandHelper())
{
    ui->setupUi(this);

    ClientSocket::initPacketHandle();

    _loaded = false;
    _command->addHelp();

    server = new QTcpServer(this);
    game = new GameEngine(this);


    connect(this, SIGNAL(newClient(ClientSocket*)), game, SLOT(connectedClient(ClientSocket*)));
}

ServerWindows::~ServerWindows()
{
    delete game;
    delete server;
    delete ui;
}

void ServerWindows::broadcast(const QByteArray &data)
{

    QMutexLocker(&this->_broadcastLock);
    foreach(ClientSocket* client, clients){
        client->write(data);
    }
}

void ServerWindows::newConnection()
{
    QMutexLocker(&this->_lock);
    while(server->hasPendingConnections()){
        this->sendMessage(tr("A new player joined the game"));

        ClientSocket* client = new ClientSocket(server->nextPendingConnection());

        clients[clientID] = client;
        client->setId(clientID);
        client->setName(tr("Player-%1").arg(clientID));
        client->setServer(this);

        ui->statusbar->showMessage(tr("Connected client: %1").arg(clients.size()));

        clientID ++;

        emit newClient(client);

        connect(client, SIGNAL(disconnected(ClientSocket*)), this, SLOT(disconnected(ClientSocket*)));
    }
}

void ServerWindows::log(const QString &message)
{
    QMutexLocker(&this->_lock);
    ui->text_console->appendPlainText(message);
}

void ServerWindows::warn(const QString &message)
{
    QMutexLocker(&this->_lock);
    ui->text_console->appendHtml("<pre style='color:#FB3;'>"+message.toHtmlEscaped()+"</pre>");
}

void ServerWindows::error(const QString &message)
{
    QMutexLocker(&this->_lock);
    ui->text_console->appendHtml("<pre style='color:#F22;'>"+message.toHtmlEscaped()+"</pre>");
}

void ServerWindows::disconnected(ClientSocket *client)
{
    QMutexLocker(&this->_lock);
    // Add a message for it
    this->sendMessage(tr("%1 left the game").arg(client->name()));

    emit disconnectedClient(client);

    // Update
    clients.remove(client->id());
    ui->statusbar->showMessage(tr("Connected client: %1").arg(clients.size()));

    client->deleteLater();
}

void ServerWindows::showEvent(QShowEvent *)
{
    if(_loaded) return;

    QMutexLocker(&this->_lock);
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

ClientSocket *ServerWindows::getBroadcastClient() const
{
    return _broadcast;
}

QHash<int, ClientSocket*> ServerWindows::getClients() const
{
    return clients;
}

void ServerWindows::sendMessage(const QString &playername, const QString &message)
{
    QMutexLocker(&this->_lock);
    Packet* p = PacketManager::serverPacket(0x01);

    QVector<QVariant> list(2);
    list[0] = playername;
    list[1] = message;

    p->writePacket(_broadcast, list);

    ui->text_chat->appendHtml("<b style='color:#6a6;'>&lt;"+playername.toHtmlEscaped()+"&gt;</b> "+message.toHtmlEscaped());
}

void ServerWindows::sendMessage(const QString &message)
{
    QMutexLocker(&this->_lock);
    Packet* p = PacketManager::serverPacket(0x01);

    QVector<QVariant> list(1);
    list[0] = message;

    p->writePacket(_broadcast, list);

    ui->text_chat->appendHtml("<i>"+message.toHtmlEscaped()+"</i>");
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
    QString message = ui->input_chat->text();
    ui->input_chat->setText("");

    if(message.startsWith("/")){
        message.remove(0, 1);

        QVariant result = _command->execute(message);
        QMutexLocker(&this->_lock);

        if(result.isNull()){
            ui->text_chat->appendHtml(tr("<i>Unknow command</i>"));
        }else{
            ui->text_chat->appendHtml(result.toString());
        }
    }else{
        this->sendMessage("Server", message);
    }
}
