#ifndef PACLET30CREATURE_H
#define PACLET30CREATURE_H

#include "packet.h"



class Packet30Creature : public Packet
{
public:
    Packet30Creature();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c,
                      quint16 player, quint8 slot, quint8 id,
                      quint8 image, quint8 damage, quint8 hp);
};

#endif // PACLET30CREATURE_H
