#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class ServerWindows;

class QScriptEngine;
class QScriptValue;

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(ServerWindows* server);

    ServerWindows *server() const;
    void setServer(ServerWindows *server);

signals:

public slots:

protected:
    QScriptEngine* _engine;
    ServerWindows* _server;

    void initMain();
    void initPacket();
    void initCards();
    void loadCard(QString scriptpath);
    void checkError();

    QScriptValue cardObject();
    QScriptValue cardObject(qint32 id);
};

#endif // GAMEENGINE_H
