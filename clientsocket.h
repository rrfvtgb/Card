#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "serverwindows.h"

#include <QObject>
#include <QTcpSocket>

class ClientSocket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(bool ready READ isReady WRITE setReady
               RESET unprepared NOTIFY becameReady)
public:
    explicit ClientSocket(QTcpSocket* socket, QObject *parent = 0);
    ~ClientSocket();

    int id() const;
    void setId(int id);

    virtual void write(const QByteArray &data);

    ServerWindows *server() const;
    void setServer(ServerWindows *server);

    QString name() const;
    void setName(QString name);

    bool isReady() const;
    void ready();
    void unprepared();
    void setReady(bool ready);


signals:
    void becameReady();
    void disconnected(ClientSocket*);

public slots:
    void read();

protected slots:
    void socketDisconnected();

protected:
    QTcpSocket* _socket;
    ServerWindows* _server;

    int _id;
    QString _name;
    bool _ready;

};

#endif // CLIENTSOCKET_H
