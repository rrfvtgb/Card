#include "clientsocket.h"
#include "gameengine.h"
#include "serverwindows.h"

#include <QDir>
#include <QSettings>
#include <QScriptEngine>
#include <QTextStream>
#include <QDebug>

#include <network/packet.h>
#include <network/packetmanager.h>

static QScriptValue clientsList(QScriptContext *context, QScriptEngine *engine)
{
    QScriptValue callee = context->thisObject();
    QObject* obj = callee.toQObject();

    if(obj != 0){
        ServerWindows* serv = dynamic_cast<ServerWindows*>(obj);

        if(serv != NULL){
            QScriptValue list = engine->newObject();
            QHash<int, ClientSocket*> hash = serv->getClients();

            foreach(ClientSocket* client, hash){
                list.setProperty(client->id(),
                                 engine->newQObject(client));
            }

            list.prototype().setProperty("size", engine->newVariant(hash.size()));

            return list;
        }
    }

    return engine->newObject();
}

GameEngine::GameEngine(ServerWindows *server) : QObject(server),
    _engine(new QScriptEngine),
    _server(server)
{
    // Register all object
    this->initMain();
    this->initCards();
    this->initPacket();

    // Call script init
    this->scriptInit();
}

ServerWindows *GameEngine::server() const
{
    return _server;
}

void GameEngine::setServer(ServerWindows *server)
{
    _server = server;
}

QScriptValue GameEngine::gameObject()
{
    return _engine->globalObject().property("game");
}

void GameEngine::connectedClient(ClientSocket *client)
{
    QScriptValue game = this->gameObject();
    QScriptValue arg = _engine->newArray();
    arg.setProperty(0, _engine->newQObject(client));

    game.property("newPlayer")
        .call(game, arg);

    checkError();
}

void GameEngine::initMain()
{
    QScriptValue game = loadObject(_server->config()->value("scriptfolder").toString() + "/game.js");
    QScriptValue server = _engine->newQObject(_server);
    server.setProperty("players", _engine->newFunction(clientsList),
                       QScriptValue::PropertyGetter);

    _engine->globalObject().setProperty("server", server);
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

void GameEngine::scriptInit()
{
    gameObject().property("init").call();
    checkError();
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
        QDir script(_server->config()->value("scriptfolder").toString());
        _server->error(tr("%1 on %2:%3").arg(
                _engine->uncaughtException().toString(),
                script.relativeFilePath(_engine->uncaughtException().property("fileName").toString()),
                QString::number(_engine->uncaughtExceptionLineNumber())));

        QStringList l = _engine->uncaughtExceptionBacktrace();
        foreach(QString trace, l){
            int filestart = trace.indexOf(" at ")+4;
            int fileend = trace.indexOf(":", filestart+7);

            if(fileend != -1){
                QString file = trace.mid(filestart, fileend-filestart);

                _server->error(tr("  %1")
                        .arg(trace.left(filestart)
                            + script.relativeFilePath(file)
                            + trace.mid(fileend)));
            }else{
                _server->error(tr("  %1").arg(trace));
            }
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
