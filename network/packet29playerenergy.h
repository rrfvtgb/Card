#ifndef PACKET29PLAYERENERGY_H
#define PACKET29PLAYERENERGY_H

#include "packet.h"



class Packet29PlayerEnergy : public Packet
{
public:
    Packet29PlayerEnergy();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player, quint8 energy);
};

#endif // PACKET29PLAYERENERGY_H
