#include <QPainter>
#include <QDebug>
#include <QTimer>

#include "cardoverlay.h"

#include "card.h"

CardOverlay::CardOverlay(QWidget *parent) : QWidget(parent),
    _ty(0),
    _card(NULL),
    _timer(new QTimer())
{
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    connect(_timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
}

void CardOverlay::paintEvent(QPaintEvent *) {
    QPainter p(this);
    //p.fillRect(rect(), QColor(80, 80, 255, 128));

    if(_card != NULL){
        QRectF r;
        QRectF r1 = rect();
        int margin = 2;

        p.setPen(QColor(0,0,0,0));
        r1.adjust(margin, margin, -margin, -margin);
        p.drawText(r1, Qt::AlignLeft&Qt::TextWordWrap, _card->tooltip(), &r);

        if(_ty > r.height()){
            _timer->stop();
            _ty = r.height();
        }

        p.setPen(Qt::white);

        r.setHeight(_ty);
        r.moveBottom(r1.bottom());
        r.adjust(-margin, -margin, margin, margin);
        p.fillRect(r, Qt::black);
        r.adjust(margin, margin, -margin, -margin);
        p.drawText(r, Qt::AlignLeft&Qt::TextWordWrap, _card->tooltip());
    }
}

Card *CardOverlay::card() const
{
    return _card;
}

void CardOverlay::setCard(Card *card)
{
    _card = card;
}

void CardOverlay::updateAnimation(){
    if(_upward){
        _ty ++;
    }else{
        _ty --;
        if(_ty <= -4){
            _ty = -4;
            _timer->stop();
        }
    }
    this->update();
}

void CardOverlay::slowShow()
{
    this->show();
    _timer->start(4);
    _upward = true;
}

void CardOverlay::slowHide()
{
    this->show();
    _timer->start(4);
    _upward = false;
}
