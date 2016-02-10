#include "packet02information.h"

Packet02Information::Packet02Information()
    :Packet(0x02)
{

}

void Packet02Information::bytesToRead(QIODevice *, ClientSocket *)
{
    /// @Todo : Throw Exception
}

void Packet02Information::bytesToWrite(ClientSocket *c, const QString &message)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(5 + message.capacity());

    this->write(data, message);

    this->packetReady(data, c);
}
