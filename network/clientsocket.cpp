#include "clientsocket.h"

#include "game.h"
#include "packet01message.h"
#include "packetmanager.h"

#include <QTcpSocket>

ClientSocket::ClientSocket(Game *parent) : SocketController(parent)
{
}

QString ClientSocket::name()
{
    return _game->playerData()->name();
}

void ClientSocket::write(const QByteArray & data)
{
    _game->socket()->write(data);
}

void ClientSocket::readMessage(const QString &playername, const QString &message)
{
    _game->receiveMessage("<"+playername+"> "+message);
}

void ClientSocket::sendMessage(const QString & message)
{
    ((Packet01Message*)PacketManager::getPacket(1))->bytesToWrite(this, message);
}

void ClientSocket::readReady()
{
    while(_game->socket()->bytesAvailable() > 1){

        int id = _game->socket()->read(1).at(0);

        Packet* p = PacketManager::getPacket(id);

        if(p != NULL){
            p->bytesToRead(_game->socket(), this);
        }else{
            qDebug() << "Invalid packet "<<id;
			_game->socket()->disconnectFromHost();
        }
    }
}
