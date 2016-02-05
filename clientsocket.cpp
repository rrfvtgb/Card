#include "clientsocket.h"

#include <QApplication>

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent) : QObject(parent),
    _socket(socket)
{
    if(socket != NULL){
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()));

        // HEADER
        socket->write((QApplication::applicationName()
                      +" v"+QApplication::applicationVersion()
                      +"\n").toUtf8());
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
