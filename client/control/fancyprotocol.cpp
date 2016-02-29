#include "fancyprotocol.h"
#include "game.h"

#include <packet.h>

#include <QApplication>
#include <QTcpSocket>

FancyProtocol::FancyProtocol(Game *parent) :
    AbstractNetworkProtocol( parent )
{

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

    /*
     * Read the protocole header
     */
    Packet* p = new Packet();
    QHash<QString, QVariant> header = p->readHeader(_game->socket());

    // Do something here with it
}

void FancyProtocol::read()
{

}

void FancyProtocol::writeMessage(const QString &message)
{

}

void FancyProtocol::rename(const QString &name)
{

}

void FancyProtocol::selectCard(quint16 id)
{

}
