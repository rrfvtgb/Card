#include "packet.h"

#include <QDateTime>
#include <QIODevice>
#include "clientsocket.h"

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

    this->write(c, str_len);

    c->append(data_str);
}

void Packet::write(QByteArray * data, quint8 value)
{
    data->append(value);
}

void Packet::write(QByteArray *data, quint16 value)
{
    data->append((quint8) (value >> 8)&0xFF);
    data->append((quint8) value&0xFF);
}

void Packet::write(QByteArray *data, quint32 value)
{
    data->append((quint8) (value >> 24)&0xFF);
    data->append((quint8) (value >> 16)&0xFF);
    data->append((quint8) (value >> 8)&0xFF);
    data->append((quint8) value&0xFF);
}

void Packet::write(QByteArray *data, quint64 value)
{
    data->append((quint8) (value >> 56)&0xFF);
    data->append((quint8) (value >> 48)&0xFF);
    data->append((quint8) (value >> 40)&0xFF);
    data->append((quint8) (value >> 32)&0xFF);
    data->append((quint8) (value >> 24)&0xFF);
    data->append((quint8) (value >> 16)&0xFF);
    data->append((quint8) (value >> 8)&0xFF);
    data->append((quint8) value&0xFF);
}

void Packet::packetReady(QByteArray *data, ClientSocket *client)
{
    data->squeeze();
    client->write(*data);

    delete data;
}

QString Packet::readString(QIODevice * device)
{
    quint32 len = this->readuint32(device);

    this->waitForByteAvailable(device, len);

    return QString::fromUtf8(device->read(len));
}

quint8 Packet::readuint8(QIODevice * device)
{
    this->waitForByteAvailable(device, 1);

    QByteArray data = device->read(1);
    return data.at(0);
}

quint16 Packet::readuint16(QIODevice *device)
{
    this->waitForByteAvailable(device, 2);

    QByteArray data = device->read(2);
    return ((quint16) data.at(0) << 8)
            + ((quint8) data.at(1));
}

quint32 Packet::readuint32(QIODevice *device)
{
    this->waitForByteAvailable(device, 4);

    QByteArray data = device->read(4);
    return ((quint32) data.at(0) << 24)
            + ((quint32) data.at(1) << 16)
            + ((quint32) data.at(2) << 8)
            + ((quint32) data.at(3));
}

quint64 Packet::readuint64(QIODevice *device)
{
    this->waitForByteAvailable(device, 8);

    QByteArray data = device->read(8);
    return ((quint64) data.at(0) << 56)
            + ((quint64) data.at(1) << 48)
            + ((quint64) data.at(2) << 40)
            + ((quint64) data.at(3) << 32)
            + ((quint64) data.at(4) << 24)
            + ((quint64) data.at(5) << 16)
            + ((quint64) data.at(6) << 8)
            + ((quint64) data.at(7));
}

void Packet::waitForByteAvailable(QIODevice *device, qint64 byte)
{
    if(device->bytesAvailable() < byte){
        qint64 time = QDateTime::currentMSecsSinceEpoch();
        qint64 delay = time + 200 + ((quint64)byte/10); // Assuming connection speed > 10KB/s


        while(time < delay
              && device->bytesAvailable() < byte){
            device->waitForReadyRead(delay - time);
            time = QDateTime::currentMSecsSinceEpoch();
        }

        if(device->bytesAvailable() < byte){
            // TODO : Throw exception
        }
    }
}
