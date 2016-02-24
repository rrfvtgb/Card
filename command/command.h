#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>

class Command : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
public:
    explicit Command(QObject *parent = 0, QString name = QString());

    QString name() const;
    void setName(const QString &name);

signals:

public slots:
    virtual bool parse(const QString& name, const QStringList& arg);

protected:
    QString _name;

    virtual bool execute(const QStringList& arg) = 0;
};

#endif // COMMAND_H
