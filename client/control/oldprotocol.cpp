#include "oldprotocol.h"

OldProtocol::OldProtocol(Game *parent) :
    AbstractNetworkProtocol(parent)
{

}

void OldProtocol::setBuffer(const QString &buffer)
{
    _buffer = buffer;
}

void OldProtocol::read()
{

}

void OldProtocol::writeMessage(const QString &message)
{

}

void OldProtocol::rename(const QString &name)
{

}

void OldProtocol::selectCard(quint16 id)
{

}
