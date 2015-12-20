#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = 0);

    QString getTooltip() const;
    void setTooltip(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    int getId() const;
    void setId(int value);

signals:

public slots:

protected:
    int id;

    QString tooltip;
    QString name;
    QString type;
};

#endif // CARD_H
