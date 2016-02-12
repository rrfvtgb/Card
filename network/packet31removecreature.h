#ifndef PACKET31REMOVECREATURE_H
#define PACKET31REMOVECREATURE_H

#include "packet.h"



class Packet31RemoveCreature : public Packet
{
public:
    Packet31RemoveCreature();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player, quint8 slot);
};

#endif // PACKET31REMOVECREATURE_H
