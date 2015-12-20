#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{

}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

int Player::getId() const
{
    return id;
}

void Player::setId(int value)
{
    id = value;
}

