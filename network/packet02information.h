#ifndef PACKET02INFORMATION_H
#define PACKET02INFORMATION_H

#include "packet.h"



class Packet02Information : public Packet
{
public:
    Packet02Information();

public slots:
    void bytesToRead(QIODevice*, ClientSocket*);
    void bytesToWrite(ClientSocket*c, const QString& message);
};

#endif // PACKET02INFORMATION_H
