#ifndef PACKET18ENABLECARD_H
#define PACKET18ENABLECARD_H

#include "packet.h"



class Packet18EnableCard : public Packet
{
public:
    Packet18EnableCard();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, quint16 card);
};

#endif // PACKET18ENABLECARD_H
