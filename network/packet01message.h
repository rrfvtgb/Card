#ifndef PACKET01MESSAGE_H
#define PACKET01MESSAGE_H

#include "packet.h"

class Packet01Message : public Packet
{
public:
    Packet01Message();

    void bytesToRead(const QByteArray&, ClientSocket*);
    QByteArray& bytesToWrite(ClientSocket*, const QString& message);
};

#endif // PACKET01MESSAGE_H
