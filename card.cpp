#include "card.h"

Card::Card(QObject *parent) : QObject(parent),
    _tooltip("???"),
    _name("???"),
    _id(0),
    _type(0),
    _speed(0),
    _mana(0),
    _energy(0)
{

}

QString Card::tooltip() const
{
    return _tooltip;
}

void Card::setTooltip(const QString &value)
{
    _tooltip = value;
}

QString Card::name() const
{
    return _name;
}

void Card::setName(const QString &value)
{
    _name = value;
}

int Card::id() const
{
    return _id;
}

void Card::setId(int value)
{
    _id = value;
}

int Card::type() const
{
    return _type;
}

void Card::setType(int value)
{
    _type = value;
}

int Card::speed() const
{
    return _speed;
}

void Card::setSpeed(int value)
{
    _speed = value;
}

int Card::mana() const
{
    return _mana;
}

void Card::setMana(int value)
{
    _mana = value;
}

int Card::energy() const
{
    return _energy;
}

void Card::setEnergy(int value)
{
    _energy = value;
}

