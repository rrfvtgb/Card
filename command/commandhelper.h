#ifndef COMMANDHELPER_H
#define COMMANDHELPER_H

#include <QObject>
#include <QMultiHash>

class Command;

class CommandHelper : public QObject
{
    Q_OBJECT
public:
    explicit CommandHelper(QObject *parent = 0);

    void addCommand(Command* s);
signals:

public slots:
    bool execute(QString command);

protected:
    QMultiHash<QString, Command*> _command;
};

#endif // COMMANDHELPER_H
