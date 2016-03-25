#include "fancyprotocol.h"
#include "game.h"
#include "oldprotocol.h"

#include <ui/gamewidget.h>

#include <QApplication>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QTcpSocket>
#include <QUrl>

Game::Game(QString address, QObject *parent) :
    QIODevice(parent),
    _socket(new QTcpSocket(this)),
    _protocol(NULL)
{
    /*
     * Connect Signal / Slot
     */
    //connect(_socket, SIGNAL(connected()), this, SLOT(deleteLater()));
    connect(_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(read()));

    /*
     * Parse address and try to connect to it
     */
    QUrl url = QUrl::fromUserInput(address);
    _socket->connectToHost(url.host(), url.port(6112));
}

Game::~Game()
{
    delete _socket;
}

QTcpSocket *Game::socket() const
{
    return _socket;
}

GameWidget *Game::widget() const
{
    return _widget;
}

void Game::setWidget(GameWidget *widget)
{
    _widget = widget;

    QLineEdit* l = _widget->findChild<QLineEdit*>("input_chat");
    connect(l, SIGNAL(returnPressed()), this, SLOT(sendMessage()));
}

void Game::receiveMessage(QString message)
{
    QTabWidget* l = _widget->findChild<QTabWidget*>("tabWidget");
    QPlainTextEdit* chat = qobject_cast<QPlainTextEdit*>( l->widget(0) );
    chat->appendHtml("<i>"+message.toHtmlEscaped()+"</i>");
}

void Game::receiveMessage(QString player, QString message)
{
    QTabWidget* l = _widget->findChild<QTabWidget*>("tabWidget");
    QPlainTextEdit* chat = qobject_cast<QPlainTextEdit*>( l->widget(0) );
    chat->appendHtml("<b>"+player.toHtmlEscaped()+"</b> <span>"+message.toHtmlEscaped()+"</span>");
}

void Game::read()
{
    if(_protocol == NULL){
        this->loadProtocol();

        // Can't see which protocol yet
        if(_protocol == NULL) return;
    }

    while(_socket->bytesAvailable() > 0){
        _protocol->read();
    }
}

void Game::loadProtocol()
{
    // Test if the first byte are the application name
    QByteArray application =
            QApplication::applicationName().toLocal8Bit();

    // Not enough byte to read ?
    if(_socket->bytesAvailable() < application.size()) return;
    QByteArray data = _socket->read(application.size());

    if(data != application){
        OldProtocol* protocol = new OldProtocol(this);
        protocol->setBuffer(QString::fromUtf8(data));
        _protocol = protocol;

        qDebug() << "Compatiblity Mode";
    }else{
        _protocol = new FancyProtocol(this);
    }
    emit connected();
}

qint64 Game::readData(char *data, qint64 maxlen)
{
    return _socket->read(data, maxlen);
}

qint64 Game::writeData(const char *data, qint64 maxlen)
{
    return _socket->write(data, maxlen);
}

void Game::sendMessage()
{
    if(_protocol == NULL){
        return;
    }

    QLineEdit* l = _widget->findChild<QLineEdit*>("input_chat");
    _protocol->writeMessage(l->text());
    l->clear();
}

Game::GameMode Game::mode() const
{
    return _mode;
}

void Game::setMode(const GameMode &mode)
{
    _mode = mode;
}

void Game::socketError(QAbstractSocket::SocketError socketError)
{
    switch(socketError){
    case QAbstractSocket::ConnectionRefusedError:
        emit closed(tr("The connection was refused by the server"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        emit closed(tr("The remote host closed the connection"));
        break;
    case QAbstractSocket::HostNotFoundError:
        emit closed(tr("The host address was not found"));
        break;
    case QAbstractSocket::SocketAccessError:
        emit closed(tr("The socket operation failed because the application lacked the required privileges"));
        break;
    case QAbstractSocket::SocketResourceError:
        emit closed(tr("The local system ran out of resources (e.g., too many sockets)"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        emit closed(tr("The socket operation timed out."));
        break;
    case QAbstractSocket::DatagramTooLargeError:
        emit closed(tr("The datagram was larger than the operating system's limit (which can be as low as 8192 bytes)"));
        break;
    case QAbstractSocket::NetworkError:
        emit closed(tr("An error occurred with the network (e.g., the network cable was accidentally plugged out)"));
        break;
    case QAbstractSocket::AddressInUseError:
        emit closed(tr("The address specified is already in use"));
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        emit closed(tr("The address specified does not belong to the host"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        emit closed(tr("The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support)."));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        emit closed(tr("The proxy requires authentication."));
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        emit closed(tr("The SSL/TLS handshake failed, so the connection was closed"));
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        emit closed(tr("The last operation attempted has not finished yet"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        emit closed(tr("Could not contact the proxy server because the connection to that server was denied"));
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        emit closed(tr("The connection to the proxy server was closed unexpectedly"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        emit closed(tr("The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        emit closed(tr("The proxy address set was not found"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        emit closed(tr("The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood"));
        break;
    case QAbstractSocket::OperationError:
        emit closed(tr("An operation was attempted while the socket was in a state that did not permit it"));
        break;
    case QAbstractSocket::SslInternalError:
        emit closed(tr("The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library."));
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        emit closed(tr("Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library."));
        break;
    case QAbstractSocket::TemporaryError:
        emit closed(tr("A temporary error occurred (e.g., operation would block and socket is non-blocking)"));
        break;
    default:
        emit closed(tr("An unidentified error occurred."));
        break;
    }
}
