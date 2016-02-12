#ifndef PACKET39HP_H
#define PACKET39HP_H

#include "packet.h"



class Packet39HP : public Packet
{
public:
    Packet39HP();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player, quint8 slot, quint8 damage);
};

#endif // PACKET39HP_H
