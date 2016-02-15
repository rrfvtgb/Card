#ifndef PACKET11CARDINFO_H
#define PACKET11CARDINFO_H

#include "packet.h"

class Packet11CardInfo: public Packet
{
public:
    Packet11CardInfo();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c,
                      quint16 cardID, quint8 type, quint8 speed,
                      quint8 mana, quint8 energy,
                      const QString&name, const QString&tooltip);
};

#endif // PACKET11CARDINFO_H
