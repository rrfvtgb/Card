#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QAbstractSocket>

class QTcpSocket;

class GameWidget;
class AbstractNetworkProtocol;

class Game : public QIODevice
{
    Q_OBJECT
public:
    enum GameMode{
        Normal      = 0x0,
        DeckBuilder = 0x1,
        Spectator   = 0x2
    };


    explicit Game(QString address, QObject *parent = 0);
    ~Game();

    QTcpSocket *socket() const;

    GameWidget *widget() const;
    void setWidget(GameWidget *widget);

    void receiveMessage(QString message);
    void receiveMessage(QString player, QString message);

    GameMode mode() const;
    void setMode(const GameMode &mode);

signals:
    /**
     * @brief closed This signal is emitted whenever the game end
     *  or we couldn't connect to the server.
     * @param reason The reason of the the end of the game
     */
    void closed(const QString& reason);

    void connected();


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

    void sendMessage();

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

    GameMode _mode;

    /**
     * @brief loadProtocol Load the correct protocol according to the first data sent
     */
    void loadProtocol();

    /*
     * Reinplemented from QIODevice
     */
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 maxlen);
};

#endif // GAME_H
