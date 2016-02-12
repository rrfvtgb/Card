#ifndef PACKET38CREATUREDAMAGE_H
#define PACKET38CREATUREDAMAGE_H

#include "packet.h"



class Packet38CreatureDamage : public Packet
{
public:
    Packet38CreatureDamage();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player, quint8 slot, quint8 damage);
};

#endif // PACKET38CREATUREDAMAGE_H
