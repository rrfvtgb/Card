#include "packet38creaturedamage.h"

Packet38CreatureDamage::Packet38CreatureDamage():Packet(0x38)
{

}

void Packet38CreatureDamage::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet38CreatureDamage::bytesToWrite(ClientSocket *c, quint16 player, quint8 slot, quint8 damage)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(5);

    this->write(data, player);
    this->write(data, slot);
    this->write(data, damage);
    this->packetReady(data, c);
}
