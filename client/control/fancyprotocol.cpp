#include "fancyprotocol.h"
#include "game.h"

#include <packet.h>
#include <packetmanager.h>

#include <QApplication>
#include <QSettings>
#include <QTcpSocket>
#include <networkexception.h>

FancyProtocol::FancyProtocol(Game *parent) :
    AbstractNetworkProtocol( parent )
{
    this->readHeader();
    this->initPacketHandle();
}

void FancyProtocol::readHeader()
{
    /*
     * Read the name of the server
     */
    QByteArray data =
            QApplication::applicationName().toLocal8Bit();

    char s;
    while((s = _game->socket()->read(1).at(0)) != '\n'){ // Read all the name
        data.append(s);
    }

    qDebug() << "Server type : " << data;
    Packet p;

    /*
     * Write the protocol header
     */
    QHash<QString, QVariant> config;
    QSettings options("option.ini", QSettings::IniFormat);

    config.insert("username", options.value("username"));
    config.insert("mode", _game->mode());

    p.writeHeader(_game->socket(), config);

    /*
     * Read the protocol header
     */
    try{
        QHash<QString, QVariant> h(p.readHeader(_game->socket()));

        QHash<QString, QVariant>::iterator it = h.begin();
        while(it != h.end()){
            it++;
        }
    }catch(NetworkException&){
        _game->socket()->disconnectFromHost();
        return;
    }

    // Do something here with it
}

void FancyProtocol::read()
{
    QTcpSocket* socket = _game->socket();
    char id = socket->read(1).at(0);
    Packet* packet = PacketManager::serverPacket(id);

    if(packet == NULL){
        socket->disconnectFromHost();
    }else{
        packet->bytesToRead(socket, _game);
    }
}

void FancyProtocol::writeMessage(const QString &message)
{
    QTcpSocket* socket = _game->socket();
    Packet* packet = PacketManager::clientPacket(0x01);

    QVector<QVariant> data(1);
    data[0] = message;
    packet->writePacket(socket, data);
}

void FancyProtocol::rename(const QString &name)
{

}

void FancyProtocol::selectCard(quint16 id)
{

}


void read01(const QVector<QVariant>& arg, QIODevice* game){
    Game* g = dynamic_cast<Game*>(game);
    g->receiveMessage(arg[0].toString(), arg[1].toString());
}

void read02(const QVector<QVariant>& arg, QIODevice* game){
    Game* g = dynamic_cast<Game*>(game);
    g->receiveMessage(arg[0].toString());
}

void FancyProtocol::initPacketHandle(){
    PacketManager::serverPacket(0x01)->setReadFunction(read01);
    PacketManager::serverPacket(0x02)->setReadFunction(read02);
}
