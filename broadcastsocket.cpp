#include "broadcastsocket.h"

#include "serverwindows.h"

BroadcastSocket::BroadcastSocket(ServerWindows * server):
    QIODevice(server)
{
    this->setServer(server);
}

qint64 BroadcastSocket::readData(char *, qint64 )
{
    return -1;
}

qint64 BroadcastSocket::writeData(const char *data, qint64 maxlen)
{
    return _server->broadcast(data, maxlen);
}

ServerWindows *BroadcastSocket::server() const
{
    return _server;
}

void BroadcastSocket::setServer(ServerWindows *server)
{
    _server = server;
}
