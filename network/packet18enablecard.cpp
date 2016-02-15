#include "packet18enablecard.h"

#include <clientsocket.h>

Packet18EnableCard::Packet18EnableCard():Packet(0x18)
{

}

void Packet18EnableCard::bytesToRead(QIODevice *device, ClientSocket *c)
{
    /// TODO: Read card
    quint16 card = this->readuint16(device);
    c->setCard(card);
}

void Packet18EnableCard::bytesToWrite(ClientSocket *c, quint16 card)
{
    QByteArray* data = this->emptyPacket();

    this->write(data, card);

    this->packetReady(data, c);
}
