#ifndef PACKET_H
#define PACKET_H

#include <QByteArray>

class ClientSocket;

class Packet
{
public:
    Packet();
    Packet(quint8 id);

    int getId();

    virtual void bytesToRead(const QByteArray&, ClientSocket*) = 0;

protected:
    quint8 _id;

    void write(ClientSocket*, QString);
    void write(ClientSocket*, quint8);

    QString readString(const QByteArray&, int &index);
    quint8 readuint8(const QByteArray&, int &index);
};

#endif // PACKET_H
