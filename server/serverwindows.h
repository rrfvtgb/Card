#ifndef SERVERWINDOWS_H
#define SERVERWINDOWS_H

#include <QHash>
#include <QObject>

#ifndef SERVER_CONSOLE
# include <QMainWindow>

namespace Ui {
class ServerWindows;
}
#endif

class QSettings;
class QTcpServer;

class ClientSocket;
class BroadcastSocket;
class GameEngine;
class CommandHelper;

class QIODevice;

#ifndef SERVER_CONSOLE
class ServerWindows : public QMainWindow
#else
class ServerWindows : public QObject
#endif
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

    void load();

signals:
#ifndef SERVER_CONSOLE
    void closed(QMainWindow*);
#endif

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
#ifndef SERVER_CONSOLE
    void showEvent(QShowEvent *);
    void closeEvent(QCloseEvent *);

    Ui::ServerWindows *ui;
#endif

    QSettings* _config;
    QTcpServer* server;

    QHash<int, ClientSocket*> clients;
    BroadcastSocket* _broadcast;
    int clientID;

    GameEngine* game;
    bool _loaded;

    CommandHelper* _command;


#ifndef SERVER_CONSOLE
private slots:
    void on_input_chat_returnPressed();
#endif
};

#endif // SERVERWINDOWS_H
