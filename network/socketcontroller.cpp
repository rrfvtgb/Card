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

void SocketController::enableCard(Card *c)
{
    _game->changeUI(Game::EnableCard, c);
}

void SocketController::disableCard(Card *c)
{
    _game->changeUI(Game::DisableCard, c);
}

void SocketController::removeCard(Card *c)
{
    _game->changeUI(Game::RemoveCard, c);
}
