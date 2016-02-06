#include "clientsocket.h"

#include <QApplication>

#include <network/packet.h>
#include <network/packetmanager.h>

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent) : QObject(parent),
    _socket(socket)
{
    if(socket != NULL){
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));

        // HEADER
        socket->write((QApplication::applicationName()
                      +" v"+QApplication::applicationVersion()
                      +"\n").toLocal8Bit());

        qDebug() << "New player connected";
    }
}

int ClientSocket::id() const
{
    return _id;
}

void ClientSocket::setId(int id)
{
    _id = id;
}

void ClientSocket::write(const QByteArray& data)
{
    _socket->write(data);
}

void ClientSocket::read()
{
    char id = _socket->read(1).at(0);
    Packet* packet = PacketManager::getPacket(id);

    if(packet == NULL){
        _socket->disconnectFromHost();
    }else{
        packet->bytesToRead(_socket, this);
    }
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
