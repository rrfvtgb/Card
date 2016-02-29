#ifndef COMPATIBILITYSOCKET_H
#define COMPATIBILITYSOCKET_H

#include "socketcontroller.h"

class CompatibilitySocket : public SocketController
{
    Q_OBJECT
public:
    explicit CompatibilitySocket(Game *parent);

    void setBuffer(const QString& buffer);
signals:

public slots:
    void readReady();
    void sendMessage(const QString&);

protected:
    QString buffer;
};

#endif // COMPATIBILITYSOCKET_H
