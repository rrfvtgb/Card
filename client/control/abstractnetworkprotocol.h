#ifndef NETWORKPROTOCOL_H
#define NETWORKPROTOCOL_H

#include <QObject>

class Game;
class Card;
class Player;
class Creep;

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
     * @brief addCard add a card in player hand
     * @param card The card data
     */
    void addCard(Card* card);

    /**
     * @brief card Get card by id
     * @param id The id of the card
     * @return The card with the id [id]
     */
    Card* getCard(quint16 id);

    /**
     * @brief addPlayer add a player on the board
     * @param player The player data
     */
    void addPlayer(Player* player);

    /**
     * @brief player Get player by id
     * @param id The id of the player
     * @return The player with the id [id]
     */
    Player* player(quint8 id);

    /**
     * @brief addCreep Add a creep for a player
     * @param playerID The player id
     * @param slot Which slot the creep goes in
     */
    void addCreep(quint8 playerID, quint8 slot);

    /**
     * @brief creep Get creep by player id and slot
     * @param playerID The player id
     * @param slot The slot where the creep is
     * @return The creep in slot [slot] of player [playerID]
     */
    Creep* creep(quint8 playerID, quint8 slot);

    /**
     * @brief _game The game information / controller
     */
    Game* _game;
};

#endif // NETWORKPROTOCOL_H
