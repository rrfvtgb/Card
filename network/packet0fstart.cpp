#include "packet0fstart.h"

Packet0FStart::Packet0FStart():
    Packet(0x0F)
{

}

void Packet0FStart::bytesToRead(QIODevice *, ClientSocket *)
{

}

void Packet0FStart::bytesToWrite(ClientSocket *, const int &)
{

}
