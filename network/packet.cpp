#include "packet.h"

#include <QDateTime>
#include <QScriptValue>
#include <clientsocket.h>

Packet::Packet():
    Packet(0, QVector<int>())
{

}

Packet::Packet(quint16 id, QVector<int> argument, PacketRead function):
    QObject(),
    _id(id),
    _argument(argument),
    _read(function)
{

}

Packet::~Packet()
{

}

int Packet::getId()
{
    return _id;
}

void Packet::setReadFunction(const PacketRead &read)
{
    _read = read;
}

void Packet::setPacketData(const QVector<int> &argument)
{
    _argument = argument;
}

QVariant Packet::private_read(int type, int &delay_max, QIODevice *socket){
    switch(type){
    case Packet::int8:
        return QVariant::fromValue(this->readuint8(socket, delay_max));
        break;
    case Packet::int16:
        return QVariant::fromValue(this->readuint16(socket, delay_max));
        break;
    case Packet::int32:
        return QVariant::fromValue(this->readuint32(socket, delay_max));
        break;
    case Packet::int64:
        return QVariant::fromValue(this->readuint64(socket, delay_max));
        break;
    case Packet::string:
    default:
        return QVariant::fromValue(this->readString(socket, delay_max));
        break;
    }
}

void Packet::private_write(int type, QVariant data, QByteArray *packet)
{
    switch(type){
    case Packet::int8:
        this->write(packet, (quint8) data.toUInt());
        break;
    case Packet::int16:
        this->write(packet, (quint16) data.toUInt());
        break;
    case Packet::int32:
        this->write(packet, (quint32) data.toUInt());
        break;
    case Packet::int64:
        this->write(packet, (quint64) data.toLongLong());
        break;
    case Packet::string:
    default:
        this->write(packet, data.toString());
        break;
    }
}

void Packet::writePacket(ClientSocket *socket, const QVector<QVariant> &data)
{
    int l = data.size();
    if(_argument.size() == l){
        QByteArray* packet = this->emptyPacket();

        for(int i=0; i<l; i++){
            int type = _argument[i];

            if((type & Packet::array) == 0){
                this->private_write(type & ~Packet::array, data[i], packet);
            }else{
                // Not available
            }
        }

        this->packetReady(packet, socket);
    } // Else throw exception
}

void Packet::writePacket(ClientSocket *socket, const QScriptValue &data)
{
    if(!data.isArray()) return; // Array expected

    int l = data.property("length").toInteger();
    if(_argument.size() == l){
        QByteArray* packet = this->emptyPacket();

        for(int i=0; i<l; i++){
            int type = _argument[i];

            if((type & Packet::array) == 0){
                this->private_write(type & ~Packet::array, data.property(i).toVariant(), packet);
            }else{
                QScriptValue subdata = data.property(i);

                if(subdata.isArray()){
                    int size = subdata.property("length").toInteger();

                    this->private_write(Packet::int8, size, packet);
                    for(int j=0; j<size; j++){
                        this->private_write(type & ~Packet::array, subdata.property(j).toVariant(), packet);
                    }
                } // Else throw script exception
            }
        }

        this->packetReady(packet, socket);
    } // Else throw exception
}

void Packet::bytesToRead(QIODevice *socket, ClientSocket *client)
{
    if(_read == NULL){
        return; // Todo : throw exception
    }

    int l = _argument.size();

    QVector<QVariant> list;
    list.resize(l);

    int delay_max = 5000 + l * 200;

    for(int i=0; i<l; i++){
        if(this->_argument[i] & Packet::array){
            delay_max = this->waitForByteAvailable(socket, 1, delay_max);
            int l = this->readuint8(socket, delay_max);

            QVector<QVariant> sublist;
            sublist.resize(l);

            for(int i=0; i<l; i++){
                sublist[i] = this->private_read(this->_argument[i] & ~Packet::array, delay_max, socket);
            }
            list[i] = QVariant::fromValue(sublist);
        }else{
            list[i] = this->private_read(this->_argument[i], delay_max, socket);
        }
    }

    this->_read(list, client);
}

QByteArray *Packet::emptyPacket(int reserveSize)
{
    QByteArray* array = new QByteArray();
    array->reserve(reserveSize);
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
    client->write(*data);

    delete data;
}

QString Packet::readString(QIODevice * device, int& delay)
{
    quint32 len = this->readuint32(device, delay);

    delay = this->waitForByteAvailable(device, len, delay);

    return QString::fromUtf8(device->read(len));
}

quint8 Packet::readuint8(QIODevice * device, int& delay)
{
    delay = this->waitForByteAvailable(device, 1, delay);

    QByteArray data = device->read(1);
    return data.at(0);
}

quint16 Packet::readuint16(QIODevice *device, int& delay)
{
    delay = this->waitForByteAvailable(device, 2, delay);

    QByteArray data = device->read(2);
    return ((quint16) data.at(0) << 8)
            + ((quint8) data.at(1));
}

quint32 Packet::readuint32(QIODevice *device, int& delay)
{
    delay = this->waitForByteAvailable(device, 4, delay);

    QByteArray data = device->read(4);
    return ((quint32) data.at(0) << 24)
            + ((quint32) data.at(1) << 16)
            + ((quint32) data.at(2) << 8)
            + ((quint32) data.at(3));
}

quint64 Packet::readuint64(QIODevice *device, int& delay)
{
    delay = this->waitForByteAvailable(device, 8, delay);

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

qint64 Packet::waitForByteAvailable(QIODevice *device, qint64 byte, qint64 max)
{
    if(device->bytesAvailable() < byte){
        qint64 time = QDateTime::currentMSecsSinceEpoch();
        qint64 delay = time + max; // Target time

        while(time < delay
              && device->bytesAvailable() < byte){
            device->waitForReadyRead(delay - time + 10);
            time = QDateTime::currentMSecsSinceEpoch();
        }

        if(device->bytesAvailable() < byte){
            // TODO : Throw exception
            return -1;
        }

        // return time remaining
        return delay - time;
    }

    // No need to wait
    return max;
}
