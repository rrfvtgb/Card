#ifndef CARDOVERLAY_H
#define CARDOVERLAY_H

#include <QWidget>

class QTimer;
class Card;

class CardOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit CardOverlay(QWidget *parent = 0);

    Card *card() const;
    void setCard(Card *card);

signals:

public slots:
    void slowShow();
    void slowHide();
    void updateAnimation();

protected:
    void paintEvent(QPaintEvent *);

    bool _upward;
    int _ty;
    Card* _card;
    QTimer* _timer;
};

#endif // CARDOVERLAY_H
