#include "packet.h"

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
