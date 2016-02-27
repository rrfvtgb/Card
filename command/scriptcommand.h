#ifndef SCRIPTCOMMAND_H
#define SCRIPTCOMMAND_H

#include "command.h"

#include <QScriptValue>

class ScriptCommand : public Command
{
public:
    ScriptCommand();

    QScriptValue *function() const;
    void setFunction(QScriptValue *function);

protected:
    QVariant execute(const QStringList& arg);

    QScriptValue* _function;
};

#endif // SCRIPTCOMMAND_H
