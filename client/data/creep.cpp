#include "creep.h"

#include <QImage>

Creep::Creep(QObject *parent): QObject(parent)
{

}

Creep::~Creep()
{
    delete _image;
}

int Creep::hp() const
{
    return _hp;
}

void Creep::setHp(int hp)
{
    _hp = hp;
    emit newValue();
}

int Creep::attack() const
{
    return _attack;
}

void Creep::setAttack(int attack)
{
    _attack = attack;
    emit newValue();
}

int Creep::id() const
{
    return _id;
}

void Creep::setId(int id)
{
    _id = id;
    emit newValue();
}

QImage *Creep::image() const
{
    return _image;
}

void Creep::setImage(QImage *image)
{
    _image = image;
    emit newValue();
}
