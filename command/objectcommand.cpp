#include "objectcommand.h"

ObjectCommand::ObjectCommand(QObject *parent, QString name):Command(parent, name)
{

}

void ObjectCommand::setExecutor(const ObjCommandExecutor &executor, QObject *object)
{
    _executor = executor;
    _object = object;

}

bool ObjectCommand::execute(const QStringList &arg)
{
    return _executor(_object, arg);
}
