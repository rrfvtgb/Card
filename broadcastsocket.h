#ifndef BROADCASTSOCKET_H
#define BROADCASTSOCKET_H

#include "clientsocket.h"

class ServerWindows;

class BroadcastSocket : public ClientSocket
{
public:
    BroadcastSocket(ServerWindows* server);

    void write(const QByteArray &data);
};

#endif // BROADCASTSOCKET_H
