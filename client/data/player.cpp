#include "creep.h"
#include "player.h"

Player::Player(QObject *parent) : QObject(parent),
    _hp(0),
    _mana(0),
    _energy(0),
    _ready(false),
    _name(""),
    _board(new Creep*[6])
{
    int i;
    for(i=0; i<6; i++){
        _board[i] = NULL;
    }
}

Player::~Player()
{
    int i;
    for(i=0; i<6; i++){
        delete _board[i];
    }
    delete _board;
}

QString Player::name() const
{
    return _name;
}

void Player::setName(const QString &value)
{
    _name = value;
    emit newValue();
}

int Player::id() const
{
    return _id;
}

void Player::setId(int value)
{
    _id = value;
}

int Player::hp() const
{
    return _hp;
}

void Player::setHp(int hp)
{
    _hp = hp;
    emit newValue();
}

int Player::mana() const
{
    return _mana;
}

void Player::setMana(int mana)
{
    _mana = mana;
    emit newValue();
}

int Player::energy() const
{
    return _energy;
}

void Player::setEnergy(int energy)
{
    _energy = energy;
    emit newValue();
}

void Player::ready()
{
    _ready = true;
    emit newValue();
}

void Player::unready()
{
    _ready = false;
    emit newValue();
}

void Player::remplaceCreep(int slot, Creep *c)
{
    if(_board[slot] != NULL){
        delete _board[slot];
    }

    _board[slot] = c;

    if(c != NULL){
        connect(c, SIGNAL(newValue()), this, SLOT(creepUpdated()));
    }

    emit newValue();
}

Creep* Player::getCreepAt(int slot)
{
    return _board[slot];
}

void Player::creepUpdated()
{
    emit newValue();
}

bool Player::isReady() const
{
    return _ready;
}

