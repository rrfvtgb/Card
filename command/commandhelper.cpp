#include "command.h"
#include "commandhelper.h"

#include <QStringList>

CommandHelper::CommandHelper(QObject *parent) : QObject(parent),
    _command()
{

}

void CommandHelper::addCommand(Command *s)
{
    if(s != NULL){
        _command.insertMulti(s->name().toLower(), s);
    }
}

bool CommandHelper::execute(QString command)
{
    QStringList argument = command.split(' ');
    QString name = command.at(0).toLower();

    argument.removeAt(0);

    QHash<QString, Command*>::iterator i = _command.find(name);

    while(i != _command.end() && i.key() == name){
        if(i.value()->parse(name, argument)){
            return true;
        }
        ++i;
    }

    return false;
}
