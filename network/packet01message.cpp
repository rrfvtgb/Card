#include "packet01message.h"

#include <QIODevice>
#include <clientsocket.h>

Packet01Message::Packet01Message()
{

}

void Packet01Message::bytesToRead(QIODevice *socket, ClientSocket *client)
{
    QString message = this->readString(socket);
    client->server()->sendMessage(client->name(), message);
}

void Packet01Message::bytesToWrite(ClientSocket * c, const QString &playername, const QString &message)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(1 + playername.capacity() + message.capacity());

    this->write(data, playername);
    this->write(data, message);

    this->packetReady(data, c);
}
