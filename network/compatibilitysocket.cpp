#include "compatibilitysocket.h"

#include <QImage>
#include <QTcpSocket>
#include <creep.h>
#include <game.h>

CompatibilitySocket::CompatibilitySocket(Game *parent) : SocketController(parent)
{

}

void CompatibilitySocket::readReady()
{
    QTcpSocket* socket = _game->socket();
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
        if(cmdID == "SAY" || cmdID == "DISP"){
            this->readMessage(subCmd.right(subCmd.length() - cmdID.size() - 1));
            // ----------------------------------------------
        }else if(cmdID == "ADDACTION" && params.size() == 2){
            int cID = params[1].toInt(&ok);

            if(ok){
                Card* c = _game->getCardById(cID);
                _game->appendCard(c);

                //emit newCard(c);

                if(_game->getMode() == Game::Classic){
                    disableCard(c);
                }
            }else{ // INVALID Card ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "START" && params.size() == 3){
            _game->setPlayerID(params[2].toInt(&ok));

            if(ok){
                Player* p = _game->playerData();

                if(p->name()==""){
                    p->setName("Me");
                }
            }else{
                qDebug() << "[Error] Player id invalid: " << params[2];
            }
            // ----------------------------------------------
        }else if(cmdID == "ACTIONON" && params.size() == 2){
            int id = params[1].toInt(&ok);

            if(ok){
                enableCard(_game->getCardById(id));
            }else{
                qDebug() << "[Error] Card id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "ACTIONOFF" && params.size() == 2){
            int id = params[1].toInt(&ok);

            if(ok){
                disableCard(_game->getCardById(id));
            }else{
                qDebug() << "[Error] Card id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "RENAME" && params.size() > 2){ // RENAME PLAYER
            int pID = params[1].toInt(&ok);

            if(ok){
                Player* p = _game->getPlayerById(pID);
                p->setName(subCmd.mid(idPos + 2 + params[1].size()));
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "CCREATE" && params.size() == 7){ // ADD CREEP
            bool ok2, ok3, ok4, ok5, ok6;

            int player = params[1].toInt(&ok);
            int slot = params[2].toInt(&ok2);
            int index = params[3].toInt(&ok3);
            int dmg = params[4].toInt(&ok4);
            int hp = params[5].toInt(&ok5);
            int image = params[6].toInt(&ok6);

            if(ok && ok2 && ok3 && ok4 && ok5 && ok6){
                Player* p = _game->getPlayerById(player);
                Creep* c = new Creep();

                c->setAttack(dmg);
                c->setHp(hp);
                c->setId(index);
                c->setImage(new QImage(":/creature/"+QString::number(image)+".png"));

                p->remplaceCreep(slot, c);
            }else{
                qDebug() << "[Error] Invalid command: " << params;
            }
            // ----------------------------------------------
        }else if(cmdID == "CKILL" && params.size() == 3){ // KILL CREEP
            bool ok2;

            int player = params[1].toInt(&ok);
            int slot = params[2].toInt(&ok2);

            if(ok && ok2){
                Player* p = _game->getPlayerById(player);
                p->remplaceCreep(slot, NULL);
            }else{
                qDebug() << "[Error] Invalid command: " << params;
            }
            // ----------------------------------------------
        }else if(cmdID == "DMG" && params.size() == 4){ // HP
            bool ok2, ok3;

            int pID = params[1].toInt(&ok);
            int slot = params[2].toInt(&ok2);
            int dmg = params[3].toInt(&ok3);

            if(ok && ok2 && ok3){
                Player* p = _game->getPlayerById(pID);

                if(slot == 4){
                    qDebug() << "Can't change damage of a player";
                }else{
                    Creep*c = p->getCreepAt(slot);

                    if(c!=NULL){
                        c->setAttack(dmg);
                    }else{
                        qDebug() << "[Error] Dead creep on slot " << slot;
                    }
                }
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "HP" && params.size() == 4){ // HP
            bool ok2, ok3;

            int pID = params[1].toInt(&ok);
            int slot = params[2].toInt(&ok2);
            int hp = params[3].toInt(&ok3);

            if(ok && ok2 && ok3){
                Player* p = _game->getPlayerById(pID);

                if(slot == 4){
                    p->setHp(hp);
                }else{
                    Creep*c = p->getCreepAt(slot);

                    if(c!=NULL){
                        c->setHp(hp);
                    }else{
                        qDebug() << "[Error] Dead creep on slot " << slot;
                    }
                }
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "MANA" && params.size() == 3){ // MANA
            bool ok2;

            int pID = params[1].toInt(&ok);
            int mana = params[2].toInt(&ok2);

            if(ok && ok2){
                Player* p = _game->getPlayerById(pID);
                p->setMana(mana);
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "ENERGY" && params.size() == 3){ // ENERGY
            bool ok2;

            int pID = params[1].toInt(&ok);
            int energy = params[2].toInt(&ok2);

            if(ok && ok2){
                Player* p = _game->getPlayerById(pID);
                p->setEnergy(energy);
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "READY" && params.size() == 2){ // READY
            int pID = params[1].toInt(&ok);

            if(ok){
                Player* p = _game->getPlayerById(pID);
                p->ready();
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "UNREADY" && params.size() == 2){ // UNREADY
            int pID = params[1].toInt(&ok);

            if(ok){
                Player* p = _game->getPlayerById(pID);
                p->unready();
            }else{ // INVALID Player ID
                qDebug() << "[Error] Player id invalid: " << params[1];
            }
            // ----------------------------------------------
        }else if(cmdID == "REMOVE" && params.size() == 3){ // REMOVE CARD
            bool ok2;

            int pID = params[1].toInt(&ok);
            int cID = params[2].toInt(&ok2);

            if(ok && ok2 && pID == _game->playerData()->id()){
                Card* c = _game->getCardById(cID);
                removeCard(c);
            }
            // ----------------------------------------------
        }else if(cmdID == "TOOLTIP" && params.size() > 2){ // ADD CARD INFO
            int cID = params[1].toInt(&ok);

            if(ok){
                Card* c = _game->getCardById(cID);

                int arg1 = idPos + 1 + params[1].size();
                int arg2 = subCmd.indexOf("\n"); // Ignore name
                int arg3 = subCmd.indexOf("\n", arg2+1); // Ignore type

                c->setName(subCmd.mid(arg1, arg2-arg1));
                c->setTooltip(subCmd.mid(arg3+1));
            }else{ // INVALID Card ID
                qDebug() << "[Error] Card id invalid: " << params[1];
            }// ----------------------------------------------
        }else if(cmdID == "ACTIONNAME" && params.size() > 2){ // ADD CARD INFO
            int cID = params[1].toInt(&ok);

            if(ok){
                Card* c = _game->getCardById(cID);

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
                Card* c = _game->getCardById(cID);

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

void CompatibilitySocket::sendMessage(const QString &message)
{
    _game->socket()->write(("SAY "+message+";").toUtf8());
}
