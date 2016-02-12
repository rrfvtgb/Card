#include "packet30creature.h"

Packet30Creature::Packet30Creature()
{

}

void Packet30Creature::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet30Creature::bytesToWrite(ClientSocket *c, quint16 player, quint8 slot, quint8 id, quint8 image, quint8 damage, quint8 hp)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(8);

    this->write(data, player);
    this->write(data, slot);
    this->write(data, id);
    this->write(data, image);
    this->write(data, damage);
    this->write(data, hp);

    this->packetReady(data, c);
}
