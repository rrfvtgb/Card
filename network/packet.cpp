#include "packet.h"

Packet::Packet():
    Packet(0)
{

}

Packet::Packet(quint8 id):
    _id(id)
{

}

int Packet::getId()
{
    return _id;
}
