#include "clientsocket.h"

#include "network/packetmanager.h"
#include "network/packet.h"


void read01(const QVector<QVariant>& arg, ClientSocket* c){
    c->server()->sendMessage(c->name(), arg[0].toString());
}

void read20(const QVector<QVariant>& arg, ClientSocket* c){
    c->setName(arg[0].toString());
}

void ClientSocket::initPacketHandle(){
    PacketManager::clientPacket(0x01)->setReadFunction(read01);
    PacketManager::clientPacket(0x20)->setReadFunction(read20);
}
