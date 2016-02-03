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

typedef QHash<int, ClientSocket*> ClientHash;

class ServerWindows : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(ClientHash players READ getClients)
public:
    explicit ServerWindows(QWidget *parent = 0);

    ServerWindows(QSettings* conf, QWidget *parent = 0);
    ~ServerWindows();

    void broadcast(const QByteArray& data);

    QSettings *config() const;
    void setConfig(QSettings *config);

    QHash<int, ClientSocket*> getClients() const;

signals:
    void closed(QMainWindow*);

public slots:
    void newConnection();

protected:
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

    Ui::ServerWindows *ui;
    QSettings* _config;
    QTcpServer* server;

    QHash<int, ClientSocket*> clients;
    int clientID;

    GameEngine* game;


private slots:
    void on_input_chat_returnPressed();
};

#endif // SERVERWINDOWS_H
