#ifndef CARD_H
#define CARD_H

#include <QObject>

class Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = 0);

    QString tooltip() const;
    void setTooltip(const QString &value);

    QString name() const;
    void setName(const QString &value);

    int id() const;
    void setId(int value);

    int type() const;
    void setType(int value);

    int speed() const;
    void setSpeed(int value);

    int mana() const;
    void setMana(int value);

    int energy() const;
    void setEnergy(int value);

signals:

public slots:

protected:
    int _id;
    int _type;
    int _speed;
    int _mana;
    int _energy;

    QString _tooltip;
    QString _name;
};

#endif // CARD_H
