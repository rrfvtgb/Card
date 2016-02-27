#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "command.h"

class CommandHelper;

class HelpCommand : public Command
{
public:
    HelpCommand(CommandHelper* commandholder);

    QString showPage(int i=1, int count=10);
    QString showCommand(QString name);

protected:
    QVariant execute(const QStringList& arg);
    CommandHelper* _commandholder;

    QString shortDescription(Command* cmd);
};

#endif // HELPCOMMAND_H
