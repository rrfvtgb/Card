#ifndef OBJECTCOMMAND_H
#define OBJECTCOMMAND_H

#include "command.h"

typedef (*ObjCommandExecutor)(QObject*, const QStringList&);

class ObjectCommand : public Command
{
public:
    explicit ObjectCommand(QObject *parent = 0, QString name = QString());

    void setExecutor(const ObjCommandExecutor &executor, QObject* object);

protected:
    bool execute(const QStringList& arg);

    ObjCommandExecutor _executor;
    QObject* _object;
};

#endif // OBJECTCOMMAND_H
