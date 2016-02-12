#include "packet11cardinfo.h"

Packet11CardInfo::Packet11CardInfo():Packet(0x11)
{

}

void Packet11CardInfo::bytesToRead(QIODevice *, ClientSocket *)
{
    /// TODO: Throw Error
}

void Packet11CardInfo::bytesToWrite(ClientSocket *c,
                                    quint8 cardID, quint8 type, quint8 speed,
                                    quint8 mana, quint8 energy,
                                    const QString &name, const QString &tooltip)
{
    QByteArray* data = this->emptyPacket();
    data->reserve(6 + name.capacity() + tooltip.capacity());

    this->write(data, cardID);
    this->write(data, type);
    this->write(data, speed);
    this->write(data, mana);
    this->write(data, energy);

    this->write(data, name);
    this->write(data, tooltip);

    this->packetReady(data, c);
}
