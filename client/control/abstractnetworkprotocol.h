#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>

class Game;

class QIODevice;

class AbstractNetworkProtocol : public QObject
{
    Q_OBJECT
public:
    explicit AbstractNetworkProtocol(Game *parent = 0);

public slots:
    /**
     * @brief read Read and parse the incomming data
     *  from the socket
     */
    virtual void read() = 0;

    /**
     * @brief writeMessage Send a message in the chat
     *  (from this player)
     * @param message The message sent
     */
    virtual void writeMessage(const QString& message) = 0;

    /**
     * @brief rename Ask the server to rename this player
     * @param name The new name of the player
     */
    virtual void rename(const QString& name) = 0;

    /**
     * @brief selectCard Tell the server that you selected a card
     * @param id Selected card id
     */
    virtual void selectCard(quint16 id) = 0;

protected:
    /**
     * @brief _game The game information / controller
     */
    Game* _game;
};

#endif // NETWORKPROTOCOL_H
