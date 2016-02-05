#include "packet.h"

#include <clientsocket.h>

Packet::Packet():
    Packet(0)
{

}

Packet::Packet(quint8 id):
    QObject(),
    _id(id)
{

}

Packet::~Packet()
{

}

int Packet::getId()
{
    return _id;
}

QByteArray *Packet::emptyPacket()
{
    QByteArray* array = new QByteArray();
    array->append(_id);
    return array;
}

void Packet::write(QByteArray * c, const QString& str)
{
    int l = c->length();

    QByteArray array = str.toUtf8();
    array.prepend(array.length());

    c->resize(l + 1 + array.length());
    c[l] = array.length();

    for(int i=0; i<array.length(); i++){
        c[i+l] = array.at(i);
    }
}
