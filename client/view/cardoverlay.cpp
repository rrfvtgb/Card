#include <QPainter>
#include <QDebug>
#include <QTimer>

#include <data/card.h>

#include "cardoverlay.h"

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

    if(_ty <= 0)
        return;

    if(_card != NULL){
        QFontMetrics fm(p.font());
        QRect r1 = rect();
        QRect r;

        int margin = 4;
        int flag = Qt::AlignLeft;

        r1.adjust(-margin, -margin, margin, margin);

        int w = r1.width() - margin*4;
        int h = fm.height();
        int x = 0;
        int y = 0;
        int s = fm.width(' ');

        QStringList lines = _card->tooltip().split('\n');
        foreach(QString line, lines){
            QStringList words = line.split(' ');
            x = 0;
            foreach(QString word, words){
                int l = fm.width(word);
                if(l + x >= w){
                    y += h;
                    x = 0;
                }
                x += l + s;
            }

            y += h;
        }
        y += h;

        //r = fm.boundingRect(r1, flag, _card->tooltip());

        /*
        p.setPen(QColor(0,0,0,0));
        r1.adjust(margin, margin, -margin, -margin);
        p.drawText(r1, Qt::AlignLeft&Qt::TextWordWrap, _card->tooltip(), &r);
        */

        if(_ty > 1){
            _timer->stop();
            _ty = 1;
        }


        p.setPen(Qt::white);

        r.setHeight(_ty * y);
        r.setRight(r1.right()-margin);
        r.moveBottom(r1.bottom()-margin);
        p.fillRect(r, QColor(0,0,0, 128));
        r.adjust(margin/2, margin/2, -margin/2, -margin/2);
        p.drawRoundedRect(r, 5.0, 5.0);
        r.adjust(margin/2, margin/2, -margin/2, -margin/2);

        y = 0;
        foreach(QString line, lines){
            QStringList words = line.split(' ');
            x = 0;
            foreach(QString word, words){
                int l = fm.width(word);
                if(l + x >= w){
                    y += h;
                    x = 0;
                }
                p.drawText(r.left() + x, r.top() + y, l, h, flag, word);
                x += l + s;
            }

            y += h;
        }
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
        _ty += 0.02;
    }else{
        _ty --;
        if(_ty <= 0){
            _ty = 0;
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
