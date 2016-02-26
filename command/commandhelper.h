#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <QObject>
#include <QMultiHash>
#include <QVariant>

class Command;

class CommandHelper : public QObject
{
    Q_OBJECT
public:
    explicit CommandHelper(QObject *parent = 0);
    ~CommandHelper();

    void addCommand(Command* s);
    void addHelp();

    const QList<Command*> getCommandsByName(QString name);

    const QList<Command*>& sortCommand();
signals:

public slots:
    QVariant execute(QString command);

protected:
    QMultiHash<QString, Command*> _command;

    QList<Command*>* _sortedCommand;
};

#endif // COMMANDHELPER_H
