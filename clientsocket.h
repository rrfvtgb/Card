#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include "serverwindows.h"

#include <QObject>
#include <QMutex>
#include <QThread>

class QTcpSocket;

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


    quint16 card() const;
    void setCard(const quint16 &card);
    void unselectCard();

    static void initPacketHandle();

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

    quint16 _card;
    int _id;
    QString _name;
    bool _ready;
    QMutex _reading;
    QMutex _writing;
    QThread _thread;
};

#endif // CLIENTSOCKET_H
