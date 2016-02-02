#include "broadcastsocket.h"

#include "serverwindows.h"

BroadcastSocket::BroadcastSocket(ServerWindows * server):
    ClientSocket(NULL, NULL)
{
    this->setId(-1);
    this->setServer(server);
}

void BroadcastSocket::write(const QByteArray &data)
{
    _server->broadcast(data);
}

