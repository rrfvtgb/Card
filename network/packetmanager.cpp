#include "packetmanager.h"

#include "packet01message.h"
#include "packet02information.h"
#include "packet0fstart.h"
#include "packet10addcard.h"
#include "packet11cardinfo.h"
#include "packet18enablecard.h"
#include "packet19disablecard.h"
#include "packet20rename.h"
#include "packet21playerready.h"
#include "packet22playerunprepared.h"
#include "packet28playermana.h"
#include "packet29playerenergy.h"
#include "packet30creature.h"
#include "packet31removecreature.h"
#include "packet38creaturedamage.h"
#include "packet39hp.h"

void __private_addPacket(Packet** list, Packet* packet){
    list[packet->getId()] = packet;
}

Packet *PacketManager::getPacket(quint8 id)
{
    return _packet[id];
}

Packet** PacketManager::_packet = PacketManager::initPacket();

Packet **PacketManager::initPacket()
{
    Packet** p = new Packet*[256];

    for(int i=0; i<256; i++){
        p[i] = NULL;
    }

    __private_addPacket(p, new Packet01Message());
    __private_addPacket(p, new Packet02Information());
    __private_addPacket(p, new Packet0FStart());
    __private_addPacket(p, new Packet10AddCard());
    __private_addPacket(p, new Packet11CardInfo());
    __private_addPacket(p, new Packet18EnableCard());
    __private_addPacket(p, new Packet19DisableCard());
    __private_addPacket(p, new Packet20Rename());
    __private_addPacket(p, new Packet21PlayerReady());
    __private_addPacket(p, new Packet22PlayerUnprepared());
    __private_addPacket(p, new Packet28PlayerMana());
    __private_addPacket(p, new Packet29PlayerEnergy());
    __private_addPacket(p, new Packet30Creature());
    __private_addPacket(p, new Packet31RemoveCreature());
    __private_addPacket(p, new Packet38CreatureDamage());
    __private_addPacket(p, new Packet39HP());

    return p;
}

