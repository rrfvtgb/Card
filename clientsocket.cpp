#include "clientsocket.h"

#include <QApplication>
#include <QTcpSocket>

#include <network/packet.h>
#include <network/packetmanager.h>

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent) : QIODevice(parent),
    _socket(socket),
    _reading(),
    _writing(),
    _thread()
{
    if(socket != NULL){
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
        connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

        // HEADER
        socket->write((QApplication::applicationName()
                      +" v"+QApplication::applicationVersion()
                      +"\n").toLocal8Bit());

        socket->moveToThread(&_thread);
        this->moveToThread(&_thread);
    }
}

ClientSocket::~ClientSocket()
{
    delete _socket;
}

int ClientSocket::id() const
{
    return _id;
}

void ClientSocket::setId(int id)
{
    _id = id;
}

void ClientSocket::read()
{
    _reading.lock();
    while(_socket->bytesAvailable() > 0){
        char id = _socket->read(1).at(0);
        Packet* packet = PacketManager::clientPacket(id);

        if(packet == NULL){
            _socket->disconnectFromHost();
            break;
        }else{
            packet->bytesToRead(_socket, this);
        }
    }
    _reading.unlock();
}

void ClientSocket::socketDisconnected()
{
    emit disconnected(this);
}

quint16 ClientSocket::card() const
{
    return _card;
}

void ClientSocket::setCard(const quint16 &card)
{
    _card = card;

    if(card == 0){
        this->setReady(false);
    }else{
        this->setReady(true);
    }
}

void ClientSocket::unselectCard()
{
    _card = 0;
    this->unprepared();
}

bool ClientSocket::isReady() const
{
    return _ready;
}

void ClientSocket::setReady(bool ready)
{
    if(ready && !_ready){
        emit becameReady();
    }
    _ready = ready;
}

void ClientSocket::ready()
{
    _ready = true;
    emit becameReady();
}

void ClientSocket::unprepared()
{
    _ready = false;
}

QString ClientSocket::name() const
{
    return _name;
}

void ClientSocket::setName(QString name)
{
    _name = name;
}

ServerWindows *ClientSocket::server() const
{
    return _server;
}

void ClientSocket::setServer(ServerWindows *server)
{
    _server = server;
}

qint64 ClientSocket::readData(char *data, qint64 maxlen)
{
    return _socket->read(data, maxlen);
}

qint64 ClientSocket::writeData(const char *data, qint64 maxlen)
{
    QMutexLocker(&(this->_writing));
    return _socket->write(data, maxlen);
}

void read01(const QVector<QVariant>& arg, QIODevice* device){
    ClientSocket* c;
    if((c = dynamic_cast<ClientSocket*>(device)) != NULL){
        c->server()->sendMessage(c->name(), arg[0].toString());
    }
}

void read20(const QVector<QVariant>& arg, QIODevice* device){
    ClientSocket* c;
    if((c = dynamic_cast<ClientSocket*>(device)) != NULL){
        c->setName(arg[0].toString());
    }
}

void ClientSocket::initPacketHandle(){
    PacketManager::clientPacket(0x01)->setReadFunction(read01);
    PacketManager::clientPacket(0x20)->setReadFunction(read20);
}

