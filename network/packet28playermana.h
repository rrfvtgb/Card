#ifndef PACKET28PLAYERMANA_H
#define PACKET28PLAYERMANA_H

#include "packet.h"



class Packet28PlayerMana : public Packet
{
public:
    Packet28PlayerMana();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 player, quint8 mana);
};

#endif // PACKET28PLAYERMANA_H
