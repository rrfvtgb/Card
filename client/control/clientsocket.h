#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "socketcontroller.h"

class Game;

class ClientSocket : public SocketController
{
    Q_OBJECT
public:
    explicit ClientSocket(Game *parent);

    QString name();
signals:

public slots:
    void write(const QByteArray&);
    void readMessage(const QString&playername, const QString&message);
    void sendMessage(const QString&);
    void readReady();
};

#endif // CLIENTSOCKET_H
