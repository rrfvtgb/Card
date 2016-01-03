#include "playerwidget.h"

#include "creep.h"
#include "player.h"

#include <QDebug>
#include <QPainter>

QImage* PlayerWidget::hp = new QImage(":/icons/hp.png");
QImage* PlayerWidget::mana = new QImage(":/icons/mana.png");
QImage* PlayerWidget::energy = new QImage(":/icons/energy.png");

PlayerWidget::PlayerWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(200, 166);
}

Player *PlayerWidget::player() const
{
    return _player;
}

void PlayerWidget::setPlayer(Player *player)
{
    _player = player;
    connect(player, SIGNAL(newValue()), this, SLOT(update()));
}

void PlayerWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QFont f = p.font();

    f.setPixelSize(16);
    p.setFont(f);

    int x = 0;

    if(_player->isReady()){
        this->drawText(&p, energy, _player->name(), x, 0);
    }else{
        this->drawText(&p, mana,   _player->name(), x, 0);
    }
    x+= 15;

    this->drawText(&p, hp,     QString::number(_player->hp()),     x, 0);
    this->drawText(&p, mana,   QString::number(_player->mana()),   x, 0);
    this->drawText(&p, energy, QString::number(_player->energy()), x, 0);

    x = 0;
    int h = this->height() - f.pixelSize()-10;

    if(h > this->width()/4){
        h = this->width()/4;
    }

    this->drawCreep(&p, 5, x, h);
    this->drawCreep(&p, 3, x, h);
    this->drawCreep(&p, 2, x, h);
    this->drawCreep(&p, 1, x, h);
}

void PlayerWidget::drawText(QPainter* p, QImage *icon, QString message, int &x, int y)
{
    QRect r;

    if(icon != NULL){
        x+= icon->width()*0.3;
        p->drawImage(x, y, *icon);
        x+= icon->width()*1.3;
    }

    p->drawText(x, y, 100, 20, Qt::AlignLeft&Qt::TextSingleLine, message, &r);

    if(r.width() <100){
        x+= r.width();
    }else{
        x+= 100;
    }
}

void PlayerWidget::drawCreep(QPainter *p, int slot, int &x, int height)
{
    Creep* c = _player->getCreepAt(slot);

    p->save();
    if(c != NULL){
        QImage* i = c->image();

        QTransform t;
        int h = i->height();
        int w = i->width();
        qreal ratio;

        if(h>w){
            ratio = height / ((qreal) h);
        }else{
            ratio = height / ((qreal) w);
        }


        t.scale(ratio, ratio);
        p->setTransform(t);
        p->drawImage((int) (x/ratio), (int) (22/ratio), *i);

        qreal sx = height/3. / hp->width();
        qreal sy = height/3. / hp->height();

        QFont f = p->font();
        f.setPixelSize(10);
        p->setPen(QColor(255, 255, 255));
        p->setFont(f);

        t.reset();
        t.scale(sx, sy);
        p->setTransform(t);
        p->drawImage((int) ((height*2./3+x)/sx), (int) ((height*2./3+22 ) /sy), *hp);
        p->drawText((int) ((height*2./3+x)/sx), (int) ((height*2./3+22 ) /sy), hp->width(), hp->height(), Qt::AlignCenter, QString::number(c->hp()));

        t.reset();
        t.scale(sx, sy);
        p->setTransform(t);
        p->drawImage((int) (x/sx), (int) ((height*2./3+22 ) /sy), *energy);
        p->drawText((int) (x/sx), (int) ((height*2./3+22 ) /sy), hp->width(), hp->height(), Qt::AlignCenter, QString::number(c->attack()));
    }
    p->restore();

    x+= height;
}

