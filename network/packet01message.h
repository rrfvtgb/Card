#ifndef PACKET01MESSAGE_H
#define PACKET01MESSAGE_H

#include "packet.h"

class Packet01Message : public Packet
{
public:
    Packet01Message();

public slots:
    void bytesToRead(QIODevice*socket, ClientSocket*client);
    void bytesToWrite(ClientSocket*c, const QString& message);
};

#endif // PACKET01MESSAGE_H
