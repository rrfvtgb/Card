#include "cardelement.h"
#include "cardoverlay.h"

#include <QGraphicsColorizeEffect>
#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>

#include <QDebug>

#include <data/card.h>

CardElement::CardElement(QWidget *parent) : QWidget(parent),
    _card(NULL),
    _cardImage(NULL),
    _overlay(NULL),
    _effect(new QGraphicsColorizeEffect)
{
    this->setGraphicsEffect(_effect);
    this->setMinimumSize(64, 64);
    this->setSizePolicy(QSizePolicy(
                            QSizePolicy::Expanding,
                            QSizePolicy::Expanding));

    _impact = 0;
    _effect->setStrength(_impact);
    _effect->setColor(QColor(0, 0, 192));

    animation = new QPropertyAnimation(this,"_impact");
    animation->setDuration(500);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->setLoopCount(1);
}

Card *CardElement::card() const
{
    return _card;
}

void CardElement::setCard(Card *card)
{
    QString path = ":/images/action/"+QString::number(card->id())+".png";

    _card = card;
    _cardImage = new QImage();
    _cardImage->load(path);

    this->update();
}

qreal CardElement::impact() const
{
    return _impact;
}

void CardElement::setImpact(const qreal &impact)
{
    _impact = impact;
    _effect->setStrength(_impact);
    this->update();
}

QSize CardElement::sizeHint() const
{
    QFont f;
    QFontMetrics fm(f);

    int w = fm.width(_card->name());
    int h = fm.height();

    return QSize(64+ w, 64+ h);
}

void CardElement::enable()
{
    animation->setDirection(QAbstractAnimation::Backward);
    if(animation->state()!=QAbstractAnimation::Running){
        animation->start();
    }
}

void CardElement::disable()
{
    animation->setDirection(QAbstractAnimation::Forward);
    if(animation->state()!=QAbstractAnimation::Running){
        animation->start();
    }
}

void CardElement::paintEvent(QPaintEvent *){
    QPainter painter(this);

    if(_cardImage != NULL){
        int x = (this->width()-_cardImage->width()) >> 1;
        painter.drawImage(x,0, *_cardImage);
    }
    if(_card != NULL){
        QFont font = painter.font();
        QTextOption textopt(Qt::AlignHCenter);
        textopt.setWrapMode(QTextOption::WordWrap);

        font.setPixelSize(16);
        painter.setFont(font);
        painter.drawText(QRectF(0, 64, this->width(),  this->height()-64), _card->name(), textopt);

        /*
        int y = 72;
        font.setPixelSize(11);
        painter.setFont(font);
        painter.drawText(QRectF(0, y, this->width(), this->height()-y), _card->tooltip(), textopt);
        */
    }
}

void CardElement::mousePressEvent(QMouseEvent *)
{
    emit onCardClicked(_card);
}

void CardElement::resizeEvent(QResizeEvent *)
{
    if(_overlay != NULL){
        _overlay->setGeometry(this->geometry());
    }
}

void CardElement::enterEvent(QEvent *)
{
    if(_overlay == NULL){
        _overlay = new CardOverlay(this->parentWidget());
        _overlay->setCard(_card);
    }
    _overlay->setGeometry(this->geometry());
    _overlay->slowShow();
}

void CardElement::leaveEvent(QEvent *)
{
    if(_overlay != NULL){
        _overlay->slowHide();
    }
}
