#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{

}

Game::~Game()
{

}

void Game::sendCommand(QString cmd)
{
    socket->write((cmd + ";").toUtf8());
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

    buffer += QString::fromUtf8(cmd);

    while((pos = buffer.indexOf(QString(";"))) != -1){
        subCmd = buffer.left(pos);
        buffer = buffer.right(buffer.size() - pos - 1);
        qDebug() << "Read << " << subCmd;

        idPos = subCmd.indexOf(' ');
        if(idPos != -1){
            cmdID = subCmd.left(idPos);
        }else{
            cmdID = subCmd;
        }

        if(cmdID == "SAY"){
            emit receiveMessage(subCmd.right(subCmd.length() - cmdID.size() - 1));
        }
        //ui->textEdit->append(subCmd);
    }

    //qDebug() << "Buffer << " << buffer;
}
