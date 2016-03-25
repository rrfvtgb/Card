#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class ServerWindows;
class ClientSocket;

class QScriptEngine;
class QScriptValue;

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(ServerWindows* server);

    ServerWindows *server() const;
    void setServer(ServerWindows *server);

    QScriptValue gameObject();

    void load();

signals:

public slots:
    void connectedClient(ClientSocket* client);

protected:
    QScriptEngine* _engine;
    ServerWindows* _server;

    void initMain();
    void initPacket();
    void initCards();
    void scriptInit();
    void loadCard(QString scriptpath);
    void checkError();

    QScriptValue cardObject();
    QScriptValue cardObject(qint32 id);
    QScriptValue loadObject(QString scriptpath);
};

#endif // GAMEENGINE_H
