#include "packet10addcard.h"

#include <clientsocket.h>

Packet10AddCard::Packet10AddCard():Packet(0x10)
{

}

void Packet10AddCard::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet10AddCard::bytesToWrite(ClientSocket *c, const QList<quint8> &card)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(1 + card.size());

    this->write(data, (quint8) card.size());
    foreach (quint8 id, card) {
        this->write(data, id);
    }

    this->packetReady(data, c);
}
