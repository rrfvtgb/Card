#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QtCore>

class Packet;

// Forward declaration of all packet
class Packet01Message;
class Packet02Information;
class Packet0FStart;
class Packet10AddCard;
class Packet11CardInfo;
class Packet18EnableCard;
class Packet19DisableCard;
class Packet20Rename;
class Packet21PlayerReady;
class Packet22PlayerUnprepared;
class Packet28PlayerMana;
class Packet29PlayerEnergy;
class Packet30Creature;
class Packet31RemoveCreature;
class Packet38CreatureDamage;
class Packet39HP;

class PacketManager
{
public:
    static Packet* getPacket(quint8 id);

private:
    static Packet** _packet;
    static Packet** initPacket();

};

#endif // PACKETMANAGER_H
