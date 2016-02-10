#include "packetmanager.h"
#include "packet01message.h"

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

    p[1] = new Packet01Message();

    return p;
}

