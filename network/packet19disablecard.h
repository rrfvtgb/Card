#ifndef PACKET19DISABLECARD_H
#define PACKET19DISABLECARD_H

#include "packet.h"



class Packet19DisableCard : public Packet
{
public:
    Packet19DisableCard();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint8 card);
};

#endif // PACKET19DISABLECARD_H
