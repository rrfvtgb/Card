#ifndef OLDPROTOCOL_H
#define OLDPROTOCOL_H

#include "abstractnetworkprotocol.h"

class OldProtocol : public AbstractNetworkProtocol
{
public:
    OldProtocol(Game* parent);

    void setBuffer(const QString &buffer);

protected:
    QString _buffer;

    // AbstractNetworkProtocol interface
public slots:
    void read();
    void writeMessage(const QString &message);
    void rename(const QString &name);
    void selectCard(quint16 id);
};

#endif // OLDPROTOCOL_H
