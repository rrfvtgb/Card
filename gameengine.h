#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

class GameEngine : public QObject
{
    Q_OBJECT
public:
    explicit GameEngine(QObject *parent = 0);

signals:

public slots:
};

#endif // GAMEENGINE_H
