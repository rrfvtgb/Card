#include "serverwindows.h"

#ifndef SERVER_CONSOLE
# include "ui_serverwindows.h"
#endif

#include "broadcastsocket.h"
#include "clientsocket.h"
#include "gameengine.h"

#include <QSettings>
#include <QTcpServer>
#include <QMutexLocker>
#include <QTcpSocket>
#include <networkexception.h>

#include <network/packet.h>
#include <network/packetmanager.h>

#include <command/commandhelper.h>

ServerWindows::ServerWindows(QWidget *parent):
    ServerWindows(new QSettings("config.ini", QSettings::IniFormat),
                  parent)
{
}

ServerWindows::ServerWindows(QSettings *conf, QWidget *parent) :
#ifndef SERVER_CONSOLE
    QMainWindow(parent),
    ui(new Ui::ServerWindows),
#else
    QObject((QObject*) parent),
#endif
    _config(conf),
    _broadcast(new BroadcastSocket(this)),
    _command(new CommandHelper())
{
#ifndef SERVER_CONSOLE
    ui->setupUi(this);
#endif

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

#ifndef SERVER_CONSOLE
    delete ui;
#endif
}

void ServerWindows::broadcast(const QByteArray &data)
{
    foreach(ClientSocket* client, clients){
        client->write(data);
    }
}

qint64 ServerWindows::broadcast(const char *data, qint64 maxlen)
{
    foreach(ClientSocket* client, clients){
        client->write(data, maxlen);
    }
    return maxlen;
}

void ServerWindows::newConnection()
{
    while(server->hasPendingConnections()){
        QTcpSocket* socket = server->nextPendingConnection();
        ClientSocket* client = new ClientSocket(socket);

        socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);

        clients[clientID] = client;
        client->setId(clientID);
        client->setName(tr("Player-%1").arg(clientID));
        client->setServer(this);

#ifndef SERVER_CONSOLE
        ui->statusbar->showMessage(tr("Connected client: %1").arg(clients.size()));
#else
        qDebug() << tr("[INFO]  Connected client: %1").arg(clients.size());
#endif

        clientID ++;

        emit newClient(client);

        connect(client, SIGNAL(closed(ClientSocket*, QString)), this, SLOT(disconnected(ClientSocket*, QString)), Qt::QueuedConnection);
    }
}

void ServerWindows::log(const QString &message)
{
#ifndef SERVER_CONSOLE
    ui->text_console->appendPlainText(message);
#else
    qDebug() << tr("[LOG]   %1").arg(message);
#endif
}

void ServerWindows::warn(const QString &message)
{
#ifndef SERVER_CONSOLE
    ui->text_console->appendHtml("<pre style='color:#FB3;'>"+message.toHtmlEscaped()+"</pre>");
#else
    qDebug() << tr("[WARN]  %1").arg(message);
#endif
}

void ServerWindows::error(const QString &message)
{
#ifndef SERVER_CONSOLE
    ui->text_console->appendHtml("<pre style='color:#F22;'>"+message.toHtmlEscaped()+"</pre>");
#else
    qDebug() << tr("[ERROR] %1").arg(message);
#endif
}

void ServerWindows::disconnected(ClientSocket *client, QString reason)
{
    // Add a message for it
    this->sendMessage(tr("%1 left the game (%2)").arg(client->name(), reason));

    emit disconnectedClient(client, reason);

    // Update
    clients.remove(client->id());

#ifndef SERVER_CONSOLE
    ui->statusbar->showMessage(tr("Connected client: %1").arg(clients.size()));
#else
     qDebug() << tr("[INFO]  Connected client: %1").arg(clients.size());
#endif

    client->deleteLater();
}

#ifndef SERVER_CONSOLE
void ServerWindows::showEvent(QShowEvent *)
{
    this->load();
}

void ServerWindows::closeEvent(QCloseEvent *)
{
    emit closed(this);
}
#endif

QIODevice *ServerWindows::getBroadcastClient() const
{
    return _broadcast;
}

void ServerWindows::load()
{
    if(_loaded) return;

    clientID = 0;

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    _loaded = server->listen(QHostAddress::Any, _config->value("port").toInt());

    if(!_loaded){
#ifndef SERVER_CONSOLE
        this->close();
#endif
    }else{
#ifndef SERVER_CONSOLE
        ui->statusbar->showMessage(tr("Server ready!"));
#else
        game->load();
        qDebug() << tr(" [INFO]  Server ready!");
#endif
    }
}

QHash<int, ClientSocket*> ServerWindows::getClients() const
{
    return clients;
}

void ServerWindows::sendMessage(const QString &playername, const QString &message)
{
    Packet* p = PacketManager::serverPacket(0x01);

    QVector<QVariant> list(2);
    list[0] = playername;
    list[1] = message;

    try{
        p->writePacket(_broadcast, list);
    }catch(...){
        qDebug() << "Can't broadcast message";
    }

#ifndef SERVER_CONSOLE
    ui->text_chat->appendHtml("<b style='color:#6a6;'>&lt;"+playername.toHtmlEscaped()+"&gt;</b> "+message.toHtmlEscaped());
#else
    qDebug() << tr("[CHAT]  %1: %2").arg(playername, message);
#endif
}

void ServerWindows::sendMessage(const QString &message)
{
    Packet* p = PacketManager::serverPacket(0x02);

    QVector<QVariant> list(1);
    list[0] = message;

    try{
        p->writePacket(_broadcast, list);
    }catch(...){
        qDebug() << "Can't broadcast message";
    }

#ifndef SERVER_CONSOLE
    ui->text_chat->appendHtml("<i>"+message.toHtmlEscaped()+"</i>");
#else
    qDebug() << tr("[INFO]  %1").arg(message);
#endif
}

QSettings *ServerWindows::config() const
{
    return _config;
}

void ServerWindows::setConfig(QSettings *config)
{
    _config = config;
}

#ifndef SERVER_CONSOLE
void ServerWindows::on_input_chat_returnPressed()
{
    QString message = ui->input_chat->text();
    ui->input_chat->setText("");

    if(message.startsWith("/")){
        message.remove(0, 1);

        QVariant result = _command->execute(message);

        if(result.isNull()){
            ui->text_chat->appendHtml(tr("<i>Unknow command</i>"));
        }else{
            ui->text_chat->appendHtml(result.toString());
        }
    }else{
        this->sendMessage("Server", message);
    }
}
#endif
