#ifndef SERVERWINDOWS_H
#define SERVERWINDOWS_H

#include <QMainWindow>
#include <QHash>
#include <QMutex>

namespace Ui {
class ServerWindows;
}

class QSettings;
class QTcpServer;

class ClientSocket;
class BroadcastSocket;
class GameEngine;
class CommandHelper;

class ServerWindows : public QMainWindow
{
    Q_OBJECT
public:
    explicit ServerWindows(QWidget *parent = 0);

    ServerWindows(QSettings* conf, QWidget *parent = 0);
    ~ServerWindows();

    void broadcast(const QByteArray& data);
    qint64 broadcast(const char*data, qint64 maxlen);

    QSettings *config() const;
    void setConfig(QSettings *config);

    QHash<int, ClientSocket*> getClients() const;

    QIODevice *getBroadcastClient() const;

signals:
    void closed(QMainWindow*);
    void newClient(ClientSocket*);
    void disconnectedClient(ClientSocket*, QString reason);

public slots:
    void log(const QString &message);
    void warn(const QString &message);
    void error(const QString &message);

    void sendMessage(const QString& playername, const QString& message);
    void sendMessage(const QString& message);

protected slots:
    void newConnection();
    void disconnected(ClientSocket*client, QString reason);

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

    Ui::ServerWindows *ui;
    QSettings* _config;
    QTcpServer* server;

    QHash<int, ClientSocket*> clients;
    BroadcastSocket* _broadcast;
    int clientID;

    GameEngine* game;
    bool _loaded;

    QMutex _lock;
    QMutex _broadcastLock;

    CommandHelper* _command;


private slots:
    void on_input_chat_returnPressed();
};

#endif // SERVERWINDOWS_H
