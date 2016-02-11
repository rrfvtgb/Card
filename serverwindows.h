#ifndef SERVERWINDOWS_H
#define SERVERWINDOWS_H

#include <QMainWindow>
#include <QHash>

namespace Ui {
class ServerWindows;
}

class QSettings;
class QTcpServer;

class ClientSocket;
class GameEngine;

class ServerWindows : public QMainWindow
{
    Q_OBJECT
public:
    explicit ServerWindows(QWidget *parent = 0);

    ServerWindows(QSettings* conf, QWidget *parent = 0);
    ~ServerWindows();

    void broadcast(const QByteArray& data);

    QSettings *config() const;
    void setConfig(QSettings *config);

    QHash<int, ClientSocket*> getClients() const;

    void sendMessage(const QString& playername, const QString& message);
    void sendMessage(const QString& message);

    ClientSocket *getBroadcastClient() const;

signals:
    void closed(QMainWindow*);
    void newClient(ClientSocket*);
    void disconnectedClient(ClientSocket*);

public slots:
    void newConnection();

protected slots:
    void disconnected(ClientSocket*client);

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

    Ui::ServerWindows *ui;
    QSettings* _config;
    QTcpServer* server;

    QHash<int, ClientSocket*> clients;
    ClientSocket* _broadcast;
    int clientID;

    GameEngine* game;
    bool _loaded;

private slots:
    void on_input_chat_returnPressed();
};

#endif // SERVERWINDOWS_H
