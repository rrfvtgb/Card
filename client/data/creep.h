#ifndef CREEP_H
#define CREEP_H

#include <QObject>


class Creep : public QObject
{
    Q_OBJECT

public:
    explicit Creep(QObject *parent = 0);
    ~Creep();

    int hp() const;
    void setHp(int hp);

    int attack() const;
    void setAttack(int attack);

    int id() const;
    void setId(int id);

    QImage *image() const;
    void setImage(QImage *image);

signals:
    void newValue();

protected:
    int _hp;
    int _attack;
    int _id;

    QImage* _image;
};

#endif // CREEP_H
