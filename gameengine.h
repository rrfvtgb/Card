#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class ServerWindows;

class QScriptEngine;

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

    void initCards();
    void loadCard(QString scriptpath);
};

#endif // GAMEENGINE_H
