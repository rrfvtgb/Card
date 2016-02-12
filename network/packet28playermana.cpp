#include "packet28playermana.h"

Packet28PlayerMana::Packet28PlayerMana():Packet(0x28)
{

}

void Packet28PlayerMana::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet28PlayerMana::bytesToWrite(ClientSocket *c, quint16 player, quint8 mana)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(4);

    this->write(data, player);
    this->write(data, mana);
    this->packetReady(data, c);
}
