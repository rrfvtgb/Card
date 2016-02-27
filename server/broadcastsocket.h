#ifndef BROADCASTSOCKET_H
#define BROADCASTSOCKET_H

#include "clientsocket.h"

class ServerWindows;

class BroadcastSocket : public QIODevice
{
public:
    BroadcastSocket(ServerWindows* server);

    ServerWindows *server() const;
    void setServer(ServerWindows *server);

protected:
    qint64 readData(char *, qint64);
    qint64 writeData(const char *data, qint64 maxlen);

    ServerWindows* _server;
};

#endif // BROADCASTSOCKET_H
