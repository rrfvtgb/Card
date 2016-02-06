#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>
#include <QObject>

class ClientSocket;
class QIODevice;

class Packet: public QObject
{
    Q_OBJECT

public:
    Packet();
    Packet(quint8 id);

    ~Packet();

    int getId();

public slots:
    virtual void bytesToRead(QIODevice*, ClientSocket*) = 0;

protected:
    quint8 _id;

    QByteArray *emptyPacket();
    void write(QByteArray*, const QString &str);
    void write(QByteArray*data, char value);
    void write(QByteArray*data, quint16 value);
    void write(QByteArray*data, quint32 value);
    void write(QByteArray*data, quint64 value);

    /// Send packet and delete it from memory
    void packetReady(QByteArray* data, ClientSocket*client);

    QString readString(QIODevice* device);
    quint8 readuint8(QIODevice*);
};

#endif // PACKET_H