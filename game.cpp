#include "game.h"

#include <QTcpSocket>

Game::Game(QObject *parent)
    : QObject(parent),
      players(),
      cards(),
      hand(),
      playerID(-1)
{

}

Game::~Game()
{

}

void Game::sendCommand(QString cmd)
{
    socket->write((cmd + ";").toUtf8());
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
    }

    return p;
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

void Game::say(QString message)
{
    this->sendCommand("SAY "+message);
}

QTcpSocket *Game::getSocket() const
{
    return socket;
}

void Game::setSocket(QTcpSocket *value)
{
    socket = value;

    connect(socket, SIGNAL(readyRead()), this, SLOT(dataReady()));

    this->dataReady();
}

void Game::dataReady(){
    int pos, idPos;
    QByteArray cmd = socket->read(socket->bytesAvailable());
    QString subCmd, cmdID;
    QStringList params;
    bool ok;

    buffer += QString::fromUtf8(cmd);

    while((pos = buffer.indexOf(QString(";"))) != -1){
        subCmd = buffer.left(pos);
        buffer = buffer.right(buffer.size() - pos - 1);
        //qDebug() << "Read << " << subCmd;

        idPos = subCmd.indexOf(' ');
        if(idPos != -1){
            cmdID = subCmd.left(idPos);
        }else{
            cmdID = subCmd;
        }

        params = subCmd.split(" ");

            // ----------------------------------------------
        if(cmdID == "SAY"){
            emit receiveMessage(subCmd.right(subCmd.length() - cmdID.size() - 1));
            // ----------------------------------------------
        }else if(cmdID == "ADDACTION" && params.size() == 2){
            int cID = params[1].toInt(&ok);

            if(ok){
                Card* c = this->getCardById(cID);
                this->hand.append(c);

                emit newCard(c);
            }else{ // INVALID Card ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "START" && params.size() == 3){
            this->playerID = params[2].toInt(&ok);

            if(!ok){
                qDebug() << "[Error] Player id invalid: " << params[2];
            }
            // ----------------------------------------------
        }else if(cmdID == "RENAME" && params.size() > 2){ // RENAME PLAYER
            int pID = params[1].toInt(&ok);

            if(ok){
                Player* p = this->getPlayerById(pID);
                p->setName(subCmd.right(idPos + 1 + params[1].size()));
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "TOOLTIP" && params.size() > 2){ // ADD CARD INFO
            int cID = params[1].toInt(&ok);

            if(ok){
                Card* c = this->getCardById(cID);

                int arg1 = idPos + 1 + params[1].size();
                int arg2 = subCmd.indexOf("\n");

                c->setName(subCmd.mid(arg1, arg2-arg1));
                c->setTooltip(subCmd.mid(arg2+1));
            }else{ // INVALID Card ID
                qDebug() << "[Error] Card id invalid: " << params[1];
            }// ----------------------------------------------
        }else if(cmdID == "ACTIONNAME" && params.size() > 2){ // ADD CARD INFO
            int cID = params[1].toInt(&ok);

            if(ok){
                Card* c = this->getCardById(cID);

                int arg1 = idPos + 2 + params[1].size();
                c->setName(subCmd.mid(arg1));
            }else{ // INVALID Card ID
                qDebug() << "[Error] Card id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "ACTIONSTATS" && params.size() == 6){ // ADD CARD INFO
            bool ok2, ok3, ok4, ok5;

            int cID = params[1].toInt(&ok);
            int type = params[2].toInt(&ok2);
            int speed = params[3].toInt(&ok3);
            int mana = params[4].toInt(&ok4);
            int energy = params[5].toInt(&ok5);

            if(ok && ok2 && ok3 && ok4 && ok5){
                Card* c = this->getCardById(cID);

                c->setType(type);
                c->setSpeed(speed);
                c->setMana(mana);
                c->setEnergy(energy);
            }
            // ----------------------------------------------
        }else{
            qDebug() << "Unknow command [" << params.size() << "] "<< subCmd;
            // ----------------------------------------------
        }
        //ui->textEdit->append(subCmd);
    }

    //qDebug() << "Buffer << " << buffer;
}
