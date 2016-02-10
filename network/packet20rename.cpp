#include "packet20rename.h"

#include <clientsocket.h>
#include <serverwindows.h>

Packet20Rename::Packet20Rename()
    :Packet(0x20)
{

}

void Packet20Rename::bytesToRead(QIODevice *socket, ClientSocket *client)
{
    QString name = this->readString(socket);

    client->setName(name);
    this->bytesToWrite(client->server()->getBroadcastClient(),
                       client->id(), name);
}

void Packet20Rename::bytesToWrite(ClientSocket *c, const quint16 &playerid, const QString &name)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(7 + name.capacity());

    this->write(data, playerid);
    this->write(data, name);

    this->packetReady(data, c);
}
