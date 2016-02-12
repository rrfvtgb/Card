#ifndef PACKET10ADDCARD_H
#define PACKET10ADDCARD_H

#include "packet.h"

class Packet10AddCard : public Packet
{
public:
    Packet10AddCard();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, const QList<quint8>& card);
};

#endif // PACKET10ADDCARD_H
