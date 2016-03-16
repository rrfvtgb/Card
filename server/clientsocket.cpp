#include "clientsocket.h"

#include <QApplication>
#include <QTcpSocket>
#include <networkexception.h>

#include <network/packet.h>
#include <network/packetmanager.h>

ClientSocket::ClientSocket(QTcpSocket *socket, QObject *parent) : QIODevice(parent),
    _socket(socket),
    _header(false)
{
    if(socket != NULL){
        connect(socket, SIGNAL(readyRead()), this, SLOT(read()), Qt::QueuedConnection);
        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)), Qt::QueuedConnection);

        // HEADER
        socket->write((QApplication::applicationName()
                      +" v"+QApplication::applicationVersion()
                      +"\n").toLocal8Bit());

        QHash<QString, QVariant> header;

        QHash<QString, QVariant>::iterator it = header.begin();
        while(it != header.end()){
            qDebug() << "[HEADER WRITE] "<<it.key()<<" = "<<it.value().toString();
            it++;
        }
        qDebug()<<"Header write ended";

        Packet p;
        p.writeHeader(socket, header);

        this->setOpenMode(QIODevice::ReadWrite);

        if(socket->bytesAvailable() > 0){
            this->read();
        }
    }
}

ClientSocket::~ClientSocket()
{
    qDebug() << this->_id << " delete";
    delete _socket;
}

int ClientSocket::id() const
{
    return _id;
}

void ClientSocket::setId(int id)
{
    _id = id;
}

void ClientSocket::read()
{
    try{
        if(!_header){
            Packet p;
            QHash<QString, QVariant> h(p.readHeader(_socket));
            QHash<QString, QVariant>::iterator it = h.begin();
            while(it != h.end()){
                qDebug() << "[HEADER] "<<it.key()<<" = "<<it.value().toString();
                it++;
            }
            qDebug() << "[HEADER] End of header";

            if(h.find("username") != h.end()){
                this->setName(h["username"].toString());
            }
            _header = true;
        }

        while(_socket->bytesAvailable() > 0){
            char id = _socket->read(1).at(0);
            Packet* packet = PacketManager::clientPacket(id);

            if(packet == NULL){
                _socket->disconnectFromHost();
                break;
            }else{
                packet->bytesToRead(_socket, this);
            }
        }
    }catch(NetworkException& ){
        _socket->disconnectFromHost();
    }
}

quint16 ClientSocket::card() const
{
    return _card;
}

void ClientSocket::setCard(const quint16 &card)
{
    _card = card;

    if(card == 0){
        this->setReady(false);
    }else{
        this->setReady(true);
    }
}

void ClientSocket::unselectCard()
{
    _card = 0;
    this->unprepared();
}

bool ClientSocket::isReady() const
{
    return _ready;
}

void ClientSocket::setReady(bool ready)
{
    if(ready && !_ready){
        emit becameReady();
    }
    _ready = ready;
}

void ClientSocket::ready()
{
    _ready = true;
    emit becameReady();
}

void ClientSocket::unprepared()
{
    _ready = false;
}

QString ClientSocket::name() const
{
    return _name;
}

void ClientSocket::setName(QString name)
{
    _name = name;
}

ServerWindows *ClientSocket::server() const
{
    return _server;
}

void ClientSocket::setServer(ServerWindows *server)
{
    _server = server;
}

qint64 ClientSocket::readData(char *data, qint64 maxlen)
{
    return _socket->read(data, maxlen);
}

qint64 ClientSocket::writeData(const char *data, qint64 maxlen)
{
    return _socket->write(data, maxlen);
}

void read01(const QVector<QVariant>& arg, QIODevice* device){
    ClientSocket* c;
    if((c = dynamic_cast<ClientSocket*>(device)) != NULL){
        c->server()->sendMessage(c->name(), arg[0].toString());
    }
}

void read20(const QVector<QVariant>& arg, QIODevice* device){
    ClientSocket* c;
    if((c = dynamic_cast<ClientSocket*>(device)) != NULL){
        c->setName(arg[0].toString());
    }
}

void ClientSocket::initPacketHandle(){
    PacketManager::clientPacket(0x01)->setReadFunction(read01);
    PacketManager::clientPacket(0x20)->setReadFunction(read20);

    qRegisterMetaType<QAbstractSocket::SocketError>();
    qRegisterMetaType<QAbstractSocket::SocketState>();
}

void ClientSocket::socketError(QAbstractSocket::SocketError socketError)
{
    switch(socketError){
    case QAbstractSocket::ConnectionRefusedError:
        emit closed(this, tr("The connection was refused by the server"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        emit closed(this, tr("The remote host closed the connection"));
        break;
    case QAbstractSocket::HostNotFoundError:
        emit closed(this, tr("The host address was not found"));
        break;
    case QAbstractSocket::SocketAccessError:
        emit closed(this, tr("The socket operation failed because the application lacked the required privileges"));
        break;
    case QAbstractSocket::SocketResourceError:
        emit closed(this, tr("The local system ran out of resources (e.g., too many sockets)"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        emit closed(this, tr("The socket operation timed out."));
        break;
    case QAbstractSocket::DatagramTooLargeError:
        emit closed(this, tr("The datagram was larger than the operating system's limit (which can be as low as 8192 bytes)"));
        break;
    case QAbstractSocket::NetworkError:
        emit closed(this, tr("An error occurred with the network (e.g., the network cable was accidentally plugged out)"));
        break;
    case QAbstractSocket::AddressInUseError:
        emit closed(this, tr("The address specified is already in use"));
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        emit closed(this, tr("The address specified does not belong to the host"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        emit closed(this, tr("The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support)."));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        emit closed(this, tr("The proxy requires authentication."));
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        emit closed(this, tr("The SSL/TLS handshake failed, so the connection was closed"));
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        emit closed(this, tr("The last operation attempted has not finished yet"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        emit closed(this, tr("Could not contact the proxy server because the connection to that server was denied"));
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        emit closed(this, tr("The connection to the proxy server was closed unexpectedly"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        emit closed(this, tr("The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        emit closed(this, tr("The proxy address set was not found"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        emit closed(this, tr("The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood"));
        break;
    case QAbstractSocket::OperationError:
        emit closed(this, tr("An operation was attempted while the socket was in a state that did not permit it"));
        break;
    case QAbstractSocket::SslInternalError:
        emit closed(this, tr("The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library."));
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        emit closed(this, tr("Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library."));
        break;
    case QAbstractSocket::TemporaryError:
        emit closed(this, tr("A temporary error occurred (e.g., operation would block and socket is non-blocking)"));
        break;
    default:
        emit closed(this, tr("An unidentified error occurred."));
        break;
    }
}
