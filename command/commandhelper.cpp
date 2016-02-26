#include "command.h"
#include "commandhelper.h"
#include "helpcommand.h"

#include <QStringList>
#include <QVariant>
#include <QDebug>

bool commandLessThan(const Command* v1, const Command* v2)
{
    return v1->name() < v2->name();
}

CommandHelper::CommandHelper(QObject *parent) : QObject(parent),
    _command(),
    _sortedCommand(NULL)
{

}

CommandHelper::~CommandHelper()
{
    if(this->_sortedCommand != NULL){
        delete _sortedCommand;
    }
}

void CommandHelper::addCommand(Command *s)
{
    if(s != NULL){
        _command.insertMulti(s->name().toLower(), s);

        if(_sortedCommand != NULL){
           std::sort(_sortedCommand->begin(), _sortedCommand->end(), commandLessThan);
        }
    }
}

void CommandHelper::addHelp()
{
    this->addCommand(new HelpCommand(this));
}

const QList<Command *> CommandHelper::getCommandsByName(QString name)
{
    name = name.toLower();
    QList<Command*> list;
    QMultiHash<QString, Command*>::iterator i = _command.find(name);

    while(i != _command.end() && i.key() == name){
        list.append(i.value());
        i++;
    }

    return list;
}

const QList<Command *> &CommandHelper::sortCommand()
{
    if(this->_sortedCommand == NULL){
        _sortedCommand = new QList<Command*>();

        foreach (Command* cmd, _command){
            _sortedCommand->append(cmd);
        }

        std::sort(_sortedCommand->begin(), _sortedCommand->end(), commandLessThan);
    }

    return *_sortedCommand;
}

QVariant CommandHelper::execute(QString command)
{
    QStringList argument = command.split(' ');
    QString name = argument.at(0).toLower();

    argument.removeAt(0);

    QMultiHash<QString, Command*>::iterator i = _command.find(name);

    while(i != _command.end() && i.key() == name){
        QVariant result = i.value()->parse(name, argument);
        if(!result.isNull()){
            return result;
        }

        i++;
    }
    qDebug()<<"exec: "<<name ;

    return QVariant();
}
