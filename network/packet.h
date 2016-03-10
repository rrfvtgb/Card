#ifndef PACKET_H
#define PACKET_H

#include <QObject>
#include <QVector>
#include <QVariant>

class QIODevice;
class QByteArray;
class QScriptValue;

typedef QVector<QVariant> VectorVariant;

Q_DECLARE_METATYPE(QVector<QVariant>)

typedef void (*PacketRead)(const QVector<QVariant>&, QIODevice*);

class Packet: public QObject
{
    Q_OBJECT

public:
    enum PacketData{
        int8 = 0x01,
        int16 = 0x02,
        int32 = 0x03,
        int64 = 0x04,

        string = 0x10,
        array = 0x20
    };

    Packet();
    Packet(quint16 id, QVector<int> argument = QVector<int>(), PacketRead function = NULL);

    ~Packet();

    int getId();

    void setReadFunction(const PacketRead &read);
    void setPacketData(const QVector<int> &argument);

public slots:
    QHash<QString, QVariant> readHeader(QIODevice* socket);
    void writeHeader(QIODevice* socket, QHash<QString, QVariant> header);

    void bytesToRead(QIODevice* socket, QIODevice*client);
    void writePacket(QIODevice* socket, const QVector<QVariant> &data);

#ifdef QTSCRIPTGLOBAL_H
    void writePacket(QIODevice* socket, const QScriptValue &data);
#endif

protected:
    quint16 _id;
    QVector<int> _argument;
    PacketRead _read;

    QByteArray *emptyPacket(int reserveSize=1);

    void write(QByteArray*, const QString &str);
    void write(QByteArray*data, quint8 value);
    void write(QByteArray*data, quint16 value);
    void write(QByteArray*data, quint32 value);
    void write(QByteArray*data, quint64 value);

    /// Send packet and delete it from memory
    void packetReady(QByteArray* data, QIODevice*client);

    QString readString(QIODevice* device, int& delay);
    quint8  readuint8 (QIODevice* device, int& delay);
    quint16 readuint16(QIODevice* device, int& delay);
    quint32 readuint32(QIODevice* device, int& delay);
    quint64 readuint64(QIODevice* device, int& delay);

    qint64 waitForByteAvailable(QIODevice* device, qint64 byte, qint64 max=2000);

    QVariant private_read(int type, int& delay_max, QIODevice *socket);
    void private_write(int type, QVariant data, QByteArray *packet);
};

#endif // PACKET_H
