#include "game.h"
#include "abstractnetworkprotocol.h"

AbstractNetworkProtocol::AbstractNetworkProtocol(Game *parent) : QObject(parent),
    _game(parent)
{

}
