#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QtCore>

class Packet;

// Forward declaration of all packet
class Packet01Message;
class Packet02Information;
class Packet0FStart;
class Packet20Rename;

class PacketManager
{
public:
    static Packet* getPacket(quint8 id);

private:
    static Packet** _packet;
    static Packet** initPacket();

};

#endif // PACKETMANAGER_H
