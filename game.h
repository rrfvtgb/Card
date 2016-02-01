#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QHash>
#include <QVector>

#include "player.h"
#include "card.h"

class QTcpSocket;

class Game : public QObject
{
    Q_OBJECT

public:
    enum GameMode{
        DeckBuilder,
        Classic
    };


    explicit Game(QObject *parent = 0);
    ~Game();

    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *value);

    GameMode getMode() const;
    void setMode(const GameMode &mode);

    QString getDeckAsString() const;
    void setNewDeck(QVector<Card*> newDeck);

    Card* getCardById(int id);

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

    void onCardClick(Card *c);

private:
    QTcpSocket* socket;
    QHash<int, Player*> players;
    QHash<int, Card*> cards;
    QVector<Card*> hand;
    QVector<Card*> deck;
    int playerID;

    QString buffer;

    Player* getPlayerById(int id);

    GameMode _mode;
};

#endif // GAME_H
