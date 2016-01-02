#ifndef CARDELEMENT_H
#define CARDELEMENT_H

#include <QWidget>

class Card;
class CardOverlay;

class CardElement : public QWidget
{
    Q_OBJECT
public:
    explicit CardElement(QWidget *parent = 0);

    Card *card() const;
    void setCard(Card *card);

signals:
    void onCardClicked(Card*c);

protected:
    Card* _card;
    QImage* _cardImage;
    CardOverlay* _overlay;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // CARDELEMENT_H
