#include "socketcontroller.h"

#include <game.h>

SocketController::SocketController(Game *parent) : QObject(parent),
    _game(parent)
{

}

void SocketController::readMessage(const QString &message)
{
    _game->receiveMessage(message);
}

void SocketController::enableCard(Card *)
{

}

void SocketController::disableCard(Card *)
{

}

void SocketController::removeCard(Card *)
{

}
