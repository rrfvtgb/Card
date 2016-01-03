#ifndef CARDELEMENT_H
#define CARDELEMENT_H

#include <QWidget>

class Card;
class CardOverlay;
class QGraphicsColorizeEffect;
class QPropertyAnimation;

class CardElement : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal _impact READ impact WRITE setImpact)
public:
    explicit CardElement(QWidget *parent = 0);

    Card *card() const;
    void setCard(Card *card);

    qreal impact() const;
    void setImpact(const qreal &impact);

public slots:
    void enable();
    void disable();

signals:
    void onCardClicked(Card*c);

protected:
    Card* _card;
    QImage* _cardImage;
    CardOverlay* _overlay;
    QGraphicsColorizeEffect* _effect;
    QPropertyAnimation * animation;
    qreal _impact;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // CARDELEMENT_H
