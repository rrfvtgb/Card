#include "cardelement.h"

#include <QImage>
#include <QMouseEvent>
#include <QPainter>

#include <QDebug>

#include "card.h"
#include "cardoverlay.h"

CardElement::CardElement(QWidget *parent) : QWidget(parent),
    _card(NULL),
    _cardImage(NULL),
    _overlay(NULL)
{
    this->setBaseSize(96, 196);
    this->setFixedWidth(108);
    this->setMinimumHeight(86);
    this->setMaximumHeight(256);
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

void CardElement::paintEvent(QPaintEvent *){
    QPainter painter(this);

    if(_cardImage != NULL){
        painter.drawImage(16,0, *_cardImage);
    }
    if(_card != NULL){
        QFont font = painter.font() ;
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
