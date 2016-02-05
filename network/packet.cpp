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
    QByteArray data_str = str.toUtf8();
    quint32 data_len = c->length();
    quint32 str_len = data_str.length();

    // Max len = 2^32-1
    c->reserve(data_len + 4 + str_len);

    c->append((char) (str_len >> 0)&0xFF);
    c->append((char) (str_len >> 8)&0xFF);
    c->append((char) (str_len >> 16)&0xFF);
    c->append((char) (str_len >> 24)&0xFF);

    c->append(data_str);
}

void Packet::write(QByteArray * data, char value)
{
    data->append(value);
}

void Packet::write(QByteArray *data, quint16 value)
{
    data->reserve(data->length() + 2);

    data->append((char) value&0xFF);
    data->append((char) (value >> 8)&0xFF);
}

void Packet::write(QByteArray *data, quint32 value)
{
    data->reserve(data->length() + 4);

    data->append((char) value&0xFF);
    data->append((char) (value >> 8)&0xFF);
    data->append((char) (value >> 16)&0xFF);
    data->append((char) (value >> 24)&0xFF);
}

void Packet::write(QByteArray *data, quint64 value)
{
    data->reserve(data->length() + 8);

    data->append((char) value&0xFF);
    data->append((char) (value >> 8)&0xFF);
    data->append((char) (value >> 16)&0xFF);
    data->append((char) (value >> 24)&0xFF);
    data->append((char) (value >> 32)&0xFF);
    data->append((char) (value >> 40)&0xFF);
    data->append((char) (value >> 48)&0xFF);
    data->append((char) (value >> 56)&0xFF);
}

void Packet::packetReady(QByteArray *data, ClientSocket *client)
{
    client->write(*data);

    delete data;
}
