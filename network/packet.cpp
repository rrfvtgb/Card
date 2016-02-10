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
    quint32 str_len = data_str.size();

    c->append((quint8) (str_len >> 24)&0xFF);
    c->append((quint8) (str_len >> 16)&0xFF);
    c->append((quint8) (str_len >> 8)&0xFF);
    c->append((quint8) (str_len >> 0)&0xFF);

    c->append(data_str);
}

void Packet::write(QByteArray * data, char value)
{
    data->append(value);
}

void Packet::write(QByteArray *data, quint16 value)
{
    data->append((quint8) value&0xFF);
    data->append((quint8) (value >> 8)&0xFF);
}

void Packet::write(QByteArray *data, quint32 value)
{
    data->append((quint8) value&0xFF);
    data->append((quint8) (value >> 8)&0xFF);
    data->append((quint8) (value >> 16)&0xFF);
    data->append((quint8) (value >> 24)&0xFF);
}

void Packet::write(QByteArray *data, quint64 value)
{
    data->append((quint8) value&0xFF);
    data->append((quint8) (value >> 8)&0xFF);
    data->append((quint8) (value >> 16)&0xFF);
    data->append((quint8) (value >> 24)&0xFF);
    data->append((quint8) (value >> 32)&0xFF);
    data->append((quint8) (value >> 40)&0xFF);
    data->append((quint8) (value >> 48)&0xFF);
    data->append((quint8) (value >> 56)&0xFF);
}

void Packet::packetReady(QByteArray *data, ClientSocket *client)
{
    data->squeeze();
    client->write(*data);

    delete data;
}

QString Packet::readString(QIODevice * device)
{
    if(device->bytesAvailable()<4){
        if(!device->waitForReadyRead(300)){
            return QString();
        }
    }

    QByteArray data_len = device->read(4);

    quint32 len = ((quint8)data_len.at(0) << 24)
                + ((quint8)data_len.at(1) << 16)
                + ((quint8)data_len.at(2) << 8)
                + (quint8)data_len.at(3);

    while(device->bytesAvailable() < len){
        if(!device->waitForReadyRead(300)){
            return QString();
        }
    }

    return QString::fromUtf8(device->read(len));
}
