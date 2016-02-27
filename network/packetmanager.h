#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H

#include <QObject>

class Packet;

class PacketManager: public QObject
{
    Q_OBJECT

public:
    PacketManager();

    static Packet* clientPacket(quint8 id);
    static Packet* serverPacket(quint8 id);

public slots: // Qt Script engine compability method
    Packet* getClientPacket(quint8 id);
    Packet* getServerPacket(quint8 id);

private:
    static Packet** _packet;
    static Packet** initPacket();

};

#endif // PACKETMANAGER_H
