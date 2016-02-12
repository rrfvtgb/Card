#include "packet18enablecard.h"

Packet18EnableCard::Packet18EnableCard():Packet(0x18)
{

}

void Packet18EnableCard::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Read card
}

void Packet18EnableCard::bytesToWrite(ClientSocket *c, quint8 card)
{
    QByteArray* data = this->emptyPacket();

    this->write(data, card);

    this->packetReady(data, c);
}
