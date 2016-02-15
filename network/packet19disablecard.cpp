#include "packet19disablecard.h"

#include <clientsocket.h>

Packet19DisableCard::Packet19DisableCard():Packet(0x19)
{

}

void Packet19DisableCard::bytesToRead(QIODevice *, ClientSocket *c)
{
    c->unselectCard();
}

void Packet19DisableCard::bytesToWrite(ClientSocket *c, quint16 card)
{
    QByteArray* data = this->emptyPacket();

    this->write(data, card);

    this->packetReady(data, c);
}
