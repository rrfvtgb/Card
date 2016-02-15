#include "packet10addcard.h"

#include <clientsocket.h>

Packet10AddCard::Packet10AddCard():Packet(0x10)
{

}

void Packet10AddCard::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Read Card (Array)
}

void Packet10AddCard::bytesToWrite(ClientSocket *c, const QList<quint16> &card)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(3 + card.size()*2);

    this->write(data, (quint16) card.size());
    foreach (quint16 id, card) {
        this->write(data, id);
    }

    this->packetReady(data, c);
}
