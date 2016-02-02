#include "gameengine.h"
#include "serverwindows.h"

#include <QDir>
#include <QSettings>
#include <QScriptEngine>
#include <QTextStream>

GameEngine::GameEngine(ServerWindows *server) : QObject(server),
    _engine(new QScriptEngine),
    _server(server)
{
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

void GameEngine::initCards()
{
    QDir script(_server->config()->value("scriptfolder").toString() + "/card");
    QStringList l = script.entryList(QDir::Files | QDir::Readable);

    _engine->globalObject().setProperty("card", _engine->newArray());

    foreach(QString card, l){
        this->loadCard(card);
    }
}

void GameEngine::loadCard(QString scriptpath)
{
    QFile f(scriptpath);

    if (!f.open(QFile::ReadOnly | QFile::Text)) return;

    QTextStream in(&f);
    QScriptValue card = _engine->evaluate(in.readAll(), scriptpath);

    if(card.isObject()){
        qint32 id = card.property("id").toInt32();
        _engine->globalObject().property("card").setProperty(id, card);
    }
}
