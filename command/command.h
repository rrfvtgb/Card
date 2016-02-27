#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QVariant>

class Command : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
public:
    explicit Command(QObject *parent = 0, QString name = QString());

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

signals:

public slots:
    virtual QVariant parse(const QString& name, const QStringList& arg);

protected:
    QString _name;
    QString _description;

    virtual QVariant execute(const QStringList& arg) = 0;
};

#endif // COMMAND_H
