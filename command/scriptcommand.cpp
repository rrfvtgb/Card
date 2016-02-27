#include "scriptcommand.h"

#include <QScriptEngine>

ScriptCommand::ScriptCommand()
{

}

QVariant ScriptCommand::execute(const QStringList &arg)
{
    if(_function != NULL
            && _function->engine() != NULL){
        return _function->call(QScriptValue(), qScriptValueFromSequence(_function->engine(), arg)).toVariant();
    }

    return QVariant();
}

QScriptValue *ScriptCommand::function() const
{
    return _function;
}

void ScriptCommand::setFunction(QScriptValue *function)
{
    _function = function;
}
