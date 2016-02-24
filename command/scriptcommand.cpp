#include "scriptcommand.h"

#include <QScriptEngine>

ScriptCommand::ScriptCommand()
{

}

bool ScriptCommand::execute(const QStringList &arg)
{
    if(_function != NULL
            && _function->engine() != NULL){
        return _function->call(QScriptValue(), qScriptValueFromSequence(_function->engine(), arg)).toBool();
    }

    return false;
}

QScriptValue *ScriptCommand::function() const
{
    return _function;
}

void ScriptCommand::setFunction(QScriptValue *function)
{
    _function = function;
}
