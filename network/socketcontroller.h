#ifndef SOCKETCONTROLLER_H
#define SOCKETCONTROLLER_H

#include <QObject>

class Game;
class Card;

class SocketController : public QObject
{
    Q_OBJECT
public:
    explicit SocketController(Game *parent);

signals:

public slots:
    virtual void readReady() = 0;
    virtual void sendMessage(const QString&) = 0;

protected:
    Game* _game;

    void readMessage(const QString&);

    void enableCard(Card*);
    void disableCard(Card*);
    void removeCard(Card*);
};

#endif // SOCKETCONTROLLER_H
