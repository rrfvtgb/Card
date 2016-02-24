#include "command.h"

Command::Command(QObject *parent, QString name) : QObject(parent),
    _name(name)
{

}

QString Command::name() const
{
    return _name;
}

void Command::setName(const QString &name)
{
    _name = name;
}

bool Command::parse(const QString &name, const QStringList &arg)
{
    if(name == _name){
        return this->execute(arg);
    }

    return false;
}
