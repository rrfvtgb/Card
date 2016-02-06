#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QtCore>

class Packet;

class PacketManager
{
public:
    static Packet* getPacket(quint8 id);

private:
    static Packet** _packet;
    static Packet** initPacket();

};

#endif // PACKETMANAGER_H
