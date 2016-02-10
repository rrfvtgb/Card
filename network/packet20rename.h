#ifndef PACKET20RENAME_H
#define PACKET20RENAME_H

#include "packet.h"


class Packet20Rename : public Packet
{
public:
    Packet20Rename();

public slots:
    void bytesToRead(QIODevice*socket, ClientSocket*client);
    void bytesToWrite(ClientSocket*c, const quint16 &playerid, const QString& name);
};

#endif // PACKET20RENAME_H
