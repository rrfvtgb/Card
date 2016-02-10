#ifndef PACKET0FSTART_H
#define PACKET0FSTART_H

#include <network/packet.h>



class Packet0FStart : public Packet
{
public:
    Packet0FStart();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, const int& playerId);
};

#endif // PACKET0FSTART_H
