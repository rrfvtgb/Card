#include "packet21playerready.h"

Packet21PlayerReady::Packet21PlayerReady():Packet(0x21)
{

}

void Packet21PlayerReady::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet21PlayerReady::bytesToWrite(ClientSocket *c, quint16 player)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(3);

    this->write(data, player);
    this->packetReady(data, c);
}
