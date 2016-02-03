#include "gameengine.h"
#include "serverwindows.h"

#include <QDir>
#include <QSettings>
#include <QScriptEngine>
#include <QTextStream>
#include <QDebug>

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
        this->loadCard(script.canonicalPath()+"/"+card);
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
        cardObject().setProperty(id, card);
    }
    checkError();
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
