#include "packet01message.h"

Packet01Message::Packet01Message()
{

}

void Packet01Message::bytesToRead(const QByteArray &, ClientSocket *)
{

}

void Packet01Message::bytesToWrite(ClientSocket * c, const QString &playername, const QString &message)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(1);

    this->write(data, playername);
    this->write(data, message);

    this->packetReady(data, c);
}
