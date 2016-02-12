#ifndef PACKET21PLAYERREADY_H
#define PACKET21PLAYERREADY_H

#include "packet.h"

class Packet21PlayerReady : public Packet
{
public:
    Packet21PlayerReady();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player);
};

#endif // PACKET21PLAYERREADY_H
