#include "packet22playerunprepared.h"

Packet22PlayerUnprepared::Packet22PlayerUnprepared():Packet(0x22)
{

}

void Packet22PlayerUnprepared::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet22PlayerUnprepared::bytesToWrite(ClientSocket *c, quint16 player)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(3);

    this->write(data, player);
    this->packetReady(data, c);
}
