#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Creep;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();

    QString name() const;
    void setName(const QString &value);

    int id() const;
    void setId(int value);

    int hp() const;
    void setHp(int hp);

    int mana() const;
    void setMana(int mana);

    int energy() const;
    void setEnergy(int energy);

    bool isReady() const;
    void ready();
    void unready();

    void remplaceCreep(int slot, Creep* c);
    Creep* getCreepAt(int slot);

signals:
    void newValue();

public slots:
    void creepUpdated();

protected:
    int _id;
    int _hp;
    int _mana;
    int _energy;

    bool _ready;

    QString _name;

    Creep** _board;
};

#endif // PLAYER_H
