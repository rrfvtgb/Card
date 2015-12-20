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
    explicit Game(QObject *parent = 0);
    ~Game();

    QTcpSocket *getSocket() const;
    void setSocket(QTcpSocket *value);

signals:
    void receiveMessage(QString message);
    void newCard(Card* c);

public slots:
    void say(QString message);

    void dataReady();

private:
    QTcpSocket* socket;
    QHash<int, Player*> players;
    QHash<int, Card*> cards;
    QVector<Card*> hand;
    int playerID;

    void sendCommand(QString cmd);
    QString buffer;

    Player* getPlayerById(int id);
    Card* getCardById(int id);
};

#endif // GAME_H
