#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;

class GameWidget;
class AbstractNetworkProtocol;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QString address, QObject *parent = 0);
    ~Game();

    QTcpSocket *socket() const;

    GameWidget *widget() const;
    void setWidget(GameWidget *widget);

signals:
    /**
     * @brief closed This signal is emitted whenever the game end
     *  or we couldn't connect to the server.
     * @param reason The reason of the the end of the game
     */
    void closed(const QString& reason);


protected slots:
    /**
     * @brief read Read the available byte on the socket
     */
    void read();

    /**
     * @brief socketError Read the error,
     *  and emit the closed signal with an human readable text
     * @param socketError The socket error that happend
     */
    void socketError(QAbstractSocket::SocketError socketError);

protected:
    /**
     * @brief _socket Connection between the client (this) and the server
     */
    QTcpSocket* _socket;

    /**
     * @brief _widget hold the widget who contains the game
     */
    GameWidget* _widget;

    /**
     * @brief _protocol contains the method to parse the socket
     */
    AbstractNetworkProtocol* _protocol;
};

#endif // GAME_H
