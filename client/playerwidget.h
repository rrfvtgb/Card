#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>

class Player;

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0);

    Player *player() const;
    void setPlayer(Player *player);

signals:

public slots:

protected:
    Player* _player;
    void paintEvent(QPaintEvent *);

    void drawText(QPainter* p, QImage* icon, QString message, int& x, int y);
    void drawCreep(QPainter* p, int slot, int& x, int height);

    static QImage* hp;
    static QImage* mana;
    static QImage* energy;
};

#endif // PLAYERWIDGET_H
