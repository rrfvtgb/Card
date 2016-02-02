#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "serverwindows.h"

#include <QObject>
#include <QTcpSocket>

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientSocket(QTcpSocket* socket, QObject *parent = 0);

    int id() const;
    void setId(int id);

    virtual void write(const QByteArray &data);

    ServerWindows *server() const;
    void setServer(ServerWindows *server);

signals:

public slots:
    void read();

protected:
    QTcpSocket* _socket;
    ServerWindows* _server;

    int _id;

};

#endif // CLIENTSOCKET_H
