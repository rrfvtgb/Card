#ifndef FANCYPROTOCOL_H
#define FANCYPROTOCOL_H

#include "abstractnetworkprotocol.h"



class FancyProtocol : public AbstractNetworkProtocol
{
public:
    FancyProtocol(Game* parent);

protected:
    void readHeader();

    // AbstractNetworkProtocol interface
public slots:
    void read();
    void writeMessage(const QString &message);
    void rename(const QString &name);
    void selectCard(quint16 id);
};

#endif // FANCYPROTOCOL_H
