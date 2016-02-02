#include "clientsocket.h"

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent) : QObject(parent),
    _socket(socket)
{
    if(socket != NULL){
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));

        // HEADER
        socket->write("MasterCard v0.0.1\n");
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

}

ServerWindows *ClientSocket::server() const
{
    return _server;
}

void ClientSocket::setServer(ServerWindows *server)
{
    _server = server;
}
