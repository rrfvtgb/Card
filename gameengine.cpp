#include "gameengine.h"
#include "serverwindows.h"

#include <QDir>
#include <QSettings>
#include <QScriptEngine>
#include <QTextStream>
#include <QDebug>

#include <network/packet.h>
#include <network/packetmanager.h>

GameEngine::GameEngine(ServerWindows *server) : QObject(server),
    _engine(new QScriptEngine),
    _server(server)
{
    this->initMain();
    this->initCards();
}

ServerWindows *GameEngine::server() const
{
    return _server;
}

void GameEngine::setServer(ServerWindows *server)
{
    _server = server;
}

void GameEngine::initMain()
{
    QScriptValue game = loadObject(_server->config()->value("scriptfolder").toString() + "/game.js");

    _engine->globalObject().setProperty("server", _engine->newQObject(_server));
    _engine->globalObject().setProperty("game",   game);
    _engine->globalObject().setProperty("card",   _engine->newArray());

    checkError();
}

void GameEngine::initPacket()
{
    QScriptValue packets = _engine->newArray(256);

    for(int i = 0; i <256; i++){
        Packet* p = PacketManager::getPacket(i);

        if(p != NULL){
            packets.setProperty(i, _engine->newQObject(p));
        }
    }

    _engine->globalObject().setProperty("packet", packets);
}

void GameEngine::initCards()
{
    QDir script(_server->config()->value("scriptfolder").toString() + "/card");
    QStringList l = script.entryList(QDir::Files | QDir::Readable);

    foreach(QString card, l){
        this->loadCard(script.canonicalPath()+"/"+card);
    }
}

void GameEngine::loadCard(QString scriptpath)
{
    QScriptValue card = loadObject(scriptpath);

    if(card.isObject()){
        qint32 id = card.property("id").toInt32();
        cardObject().setProperty(id, card);
    }

}

void GameEngine::checkError()
{
    if(_engine->hasUncaughtException()){
        qDebug("%s on %s:%d",
               _engine->uncaughtException().toString().toStdString().c_str(),
               _engine->uncaughtException().property("fileName").toString().toStdString().c_str(),
               _engine->uncaughtExceptionLineNumber());

        QStringList l = _engine->uncaughtExceptionBacktrace();
        foreach(QString trace, l){
            qDebug("  %s", trace.toStdString().c_str());
        }
    }
}

QScriptValue GameEngine::cardObject()
{
    return _engine->globalObject().property("card");
}

QScriptValue GameEngine::cardObject(qint32 id)
{
    return cardObject().property(id);
}

QScriptValue GameEngine::loadObject(QString scriptpath)
{
    QFile f(scriptpath);

    if (!f.open(QFile::ReadOnly | QFile::Text)) return QScriptValue();

    QTextStream in(&f);
    QScriptValue card = _engine->evaluate(in.readAll(), scriptpath);

    checkError();
    return card;
}
