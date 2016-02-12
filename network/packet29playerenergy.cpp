#include "packet29playerenergy.h"

Packet29PlayerEnergy::Packet29PlayerEnergy():Packet(0x29)
{

}

void Packet29PlayerEnergy::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet29PlayerEnergy::bytesToWrite(ClientSocket *c, quint16 player, quint8 energy)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(4);

    this->write(data, player);
    this->write(data, energy);
    this->packetReady(data, c);
}
