#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QHash>
#include <QVector>

#include "player.h"
#include "card.h"

class QTcpSocket;
class SocketController;

class Game : public QObject
{
    Q_OBJECT

public:
    enum GameMode{
        DeckBuilder,
        Classic
    };

    enum NetworkInformation{
        EnableCard,
        DisableCard,
        RemoveCard
    };


    explicit Game(QObject *parent = 0);
    ~Game();

    QTcpSocket *socket() const;
    void setSocket(QTcpSocket *value);

    GameMode getMode() const;
    void setMode(const GameMode &mode);

    QString getDeckAsString() const;
    void setNewDeck(QVector<Card*> newDeck);

    Card* getCardById(int id);
    Player* getPlayerById(int id);

    Player* playerData();

    void setPlayerID(int value);
    void changeUI(const NetworkInformation& information, Card* card);

signals:
    void receiveMessage(QString message);

    void newCard(Card* c);
    void removeCard(Card* c);
    void newPlayer(Player* p);

    void disableCard(Card* c);
    void enableCard(Card* c);

public slots:
    void say(QString message);

    void dataReady();
    void sendCommand(QString cmd);

    void appendCard(Card* c);
    void onCardClick(Card *c);

    void reset();

private:
    QTcpSocket *_socket;
    QHash<int, Player*> players;
    QHash<int, Card*> cards;
    QVector<Card*> hand;
    QVector<Card*> deck;
    int playerID;

    GameMode _mode;
    SocketController* _network;
};

#endif // GAME_H
