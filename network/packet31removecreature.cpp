#include "packet31removecreature.h"

Packet31RemoveCreature::Packet31RemoveCreature():Packet(0x31)
{

}

void Packet31RemoveCreature::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet31RemoveCreature::bytesToWrite(ClientSocket *c, quint16 player, quint8 slot)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(4);

    this->write(data, player);
    this->write(data, slot);
    this->packetReady(data, c);
}
