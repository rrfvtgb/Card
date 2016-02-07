#include "creep.h"
#include "game.h"

#include <QApplication>
#include <QImage>
#include <QTcpSocket>

#include <network/clientsocket.h>
#include <network/compatibilitysocket.h>

Game::Game(QObject *parent)
    : QObject(parent),
      players(),
      cards(),
      hand(),
      playerID(-1),
      _mode(Classic),
      _network(NULL)
{

}

Game::~Game()
{

}

void Game::sendCommand(QString cmd)
{
    _socket->write((cmd + ";").toUtf8());
}

void Game::appendCard(Card *c)
{
    this->hand.append(c);
}

void Game::onCardClick(Card *c)
{
    switch(_mode){
    case DeckBuilder:
        if(deck.contains(c)){
            deck.removeOne(c);
            emit disableCard(c);
        }else if(deck.length()<20){
            deck.append(c);
            emit enableCard(c);
        }
        break;
    case Classic:
        this->sendCommand("ACTION "+QString::number(c->id()));
        break;
    }
}

void Game::reset()
{
    delete _network;
    _network = NULL;

    deck.clear();
    hand.clear();
    players.clear();
    cards.clear();
}

void Game::setPlayerID(int value)
{
    playerID = value;
}

Player *Game::getPlayerById(int id)
{
    QHash<int, Player*>::iterator it = this->players.find(id);
    Player* p;

    if(it != this->players.end()){ // Player exist
        p = it.value();

    }else{ // Insert new Player
        p = new Player();

        p->setId(id);
        this->players.insert(id, p);

        emit newPlayer(p);
    }

    return p;
}

Player *Game::playerData()
{
    return this->getPlayerById(this->playerID);
}

Card *Game::getCardById(int id)
{
    QHash<int, Card*>::iterator it = this->cards.find(id);
    Card* c;

    if(it != this->cards.end()){ // Card exist
        c = it.value();

    }else{ // Insert new card
        c = new Card();

        c->setId(id);
        this->cards.insert(id, c);
    }

    return c;
}

Game::GameMode Game::getMode() const
{
    return _mode;
}

void Game::setMode(const GameMode &mode)
{
    _mode = mode;
}

QString Game::getDeckAsString() const
{
    QString s;
    foreach(Card*c, deck){
        s+=" "+QString::number(c->id());
    }
    return s;
}

void Game::setNewDeck(QVector<Card *> newDeck)
{
    foreach(Card* c, deck){
        emit disableCard(c);
    }
    foreach(Card* c, newDeck){
        emit enableCard(c);
    }
    deck = newDeck;
}

void Game::say(QString message)
{
    if(_network == NULL) _network = new CompatibilitySocket(this); // The server should be an old version
    _network->sendMessage(message);
}

QTcpSocket *Game::socket() const
{
    return _socket;
}

void Game::setSocket(QTcpSocket *value)
{
    _socket = value;

    connect(_socket, SIGNAL(readyRead()), this, SLOT(dataReady()));

    this->dataReady();
}

void Game::dataReady(){
    if(_network == NULL){
        QByteArray application = QApplication::applicationName().toLocal8Bit();

        if(_socket->bytesAvailable() < application.size()) return;

        bool old = _socket->bytesAvailable() < application.size();

        if(!old){
            // Test header
            QByteArray firstCommand = _socket->read(application.size());

            if(firstCommand != application){
                old = true;
            }
        }

        if(old){
            _network = new CompatibilitySocket(this);
            qDebug() << "Compatiblity Mode";
        }else{
            _network = new ClientSocket(this);

            char s;
            while((s = _socket->read(1).at(0)) != '\n'){ // Cleanup header
                application.append(s);
            }

            qDebug() << "Server type : " << application;
        }

        connect(_socket, SIGNAL(readyRead()), this, SLOT(dataReady()));
    }

    _network->readReady();
}
