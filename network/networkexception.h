#ifndef NETWORKEXCEPTION_H
#define NETWORKEXCEPTION_H

#include <QException>


class NetworkException : public QException
{
public:
    void raise() const { throw *this; }
    NetworkException *clone() const { return new NetworkException(*this); }
};

#endif // NETWORKEXCEPTION_H
