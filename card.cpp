#include "card.h"

Card::Card(QObject *parent) : QObject(parent)
{

}

QString Card::getTooltip() const
{
    return tooltip;
}

void Card::setTooltip(const QString &value)
{
    tooltip = value;
}

QString Card::getName() const
{
    return name;
}

void Card::setName(const QString &value)
{
    name = value;
}

QString Card::getType() const
{
    return type;
}

void Card::setType(const QString &value)
{
    type = value;
}

int Card::getId() const
{
    return id;
}

void Card::setId(int value)
{
    id = value;
}

