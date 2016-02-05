#include "packet01message.h"

Packet01Message::Packet01Message()
{

}

void Packet01Message::bytesToRead(const QByteArray &, ClientSocket *)
{

}

void Packet01Message::bytesToWrite(ClientSocket * c, const QString &playername, const QString &message)
{
    this->write(c, playername);
    this->write(c, message);
}
