#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTcpSocket>

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

public slots:
    void say(QString message);

    void dataReady();

private:
    QTcpSocket* socket;

    void sendCommand(QString cmd);
    QString buffer;
};

#endif // GAME_H
