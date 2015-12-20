#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);

    QString getName() const;
    void setName(const QString &value);

    int getId() const;
    void setId(int value);

signals:

public slots:

protected:
    int id;

    QString name;

};

#endif // PLAYER_H
