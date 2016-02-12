#include "packet19disablecard.h"

Packet19DisableCard::Packet19DisableCard():Packet(0x19)
{

}

void Packet19DisableCard::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Read card
}

void Packet19DisableCard::bytesToWrite(ClientSocket *c, quint8 card)
{
    QByteArray* data = this->emptyPacket();

    this->write(data, card);

    this->packetReady(data, c);
}
