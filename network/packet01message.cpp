#include "packet01message.h"
#include "clientsocket.h"

#include <QIODevice>
#include <QDebug>

Packet01Message::Packet01Message():Packet(1)
{

}

void Packet01Message::bytesToRead(QIODevice *socket, ClientSocket *client)
{
    QString player  = this->readString(socket);
    QString message = this->readString(socket);
    client->readMessage(player, message);
}

void Packet01Message::bytesToWrite(ClientSocket * c, const QString &message)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(5 + message.capacity());

    this->write(data, message);

    this->packetReady(data, c);
}
