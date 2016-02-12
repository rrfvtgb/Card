#include "packet39hp.h"

Packet39HP::Packet39HP():Packet(0x39)
{

}

void Packet39HP::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet39HP::bytesToWrite(ClientSocket *c, quint16 player, quint8 slot, quint8 damage)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(5);

    this->write(data, player);
    this->write(data, slot);
    this->write(data, damage);
    this->packetReady(data, c);
}
