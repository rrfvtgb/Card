#ifndef PACKET22PLAYERUNPREPARED_H
#define PACKET22PLAYERUNPREPARED_H

#include "packet.h"



class Packet22PlayerUnprepared : public Packet
{
public:
    Packet22PlayerUnprepared();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player);
};

#endif // PACKET22PLAYERUNPREPARED_H
