#include "scriptcommand.h"

#ifdef QTSCRIPTGLOBAL_H
# include <QScriptEngine>
# include <QScriptValue>
#endif

ScriptCommand::ScriptCommand()
{

}

#ifdef QTSCRIPTGLOBAL_H
QVariant ScriptCommand::execute(const QStringList &arg)
{
    if(_function != NULL
            && _function->engine() != NULL){
        return _function->call(QScriptValue(), qScriptValueFromSequence(_function->engine(), arg)).toVariant();
    }
#else
QVariant ScriptCommand::execute(const QStringList &)
{
#endif

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
