#include "command.h"

#include <QVariant>

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

QVariant Command::parse(const QString &name, const QStringList &arg)
{
    if(name == _name.toLower()){
        return this->execute(arg);
    }

    return false;
}

QString Command::description() const
{
    return _description;
}

void Command::setDescription(const QString &description)
{
    _description = description;
}
