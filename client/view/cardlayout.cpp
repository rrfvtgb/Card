#include <QtMath>
#include <QDebug>

#include "cardlayout.h"

CardLayout::CardLayout(): QLayout()
{

}

CardLayout::CardLayout(QWidget *parent): QLayout(parent)
{

}

CardLayout::~CardLayout()
{
     QLayoutItem *item;
     while ((item = takeAt(0)))
         delete item;
}

int CardLayout::count() const
{
    // QList::size() returns the number of QLayoutItems in the list
    return list.size();
}

QLayoutItem *CardLayout::itemAt(int idx) const
{
    // QList::value() performs index checking, and returns 0 if we are
    // outside the valid range
    return list.value(idx);
}

QLayoutItem *CardLayout::takeAt(int idx)
{
    // QList::take does not do index checking
    return idx >= 0 && idx < list.size() ? list.takeAt(idx) : 0;
}

void CardLayout::addItem(QLayoutItem *item)
{
    list.append(item);
}

void CardLayout::setGeometry(const QRect &r)
{
    QLayout::setGeometry(r);

    if (list.size() == 0)
        return;

    int s = spacing();

    int h = this->itemCountH();
    int w = this->itemCountV();

    int rw = (r.width() - (w - 1) * s)  / w;
    int rh = (r.height() - (h - 1) * s) / h;

    int i = 0;
    int itemX = 0;
    int itemY = 0;

    while (i < list.size()) {
        QLayoutItem *o = list.at(i);
        QRect geom(r.left() + itemX * (rw + s) - s, r.top() + itemY * (rh + s) - s, rw, rh);
        o->setGeometry(geom);

        itemX++;

        if(itemX == w){
            itemX = 0;
            itemY++;
        }

        i++;
    }
}

int CardLayout::itemCountH() const
{
    int n = this->count();
    qreal w = qCeil(qSqrt(n));

    return qCeil(n/w);
}

int CardLayout::itemCountV() const
{
    int n = this->count();
    int w = qCeil(qSqrt(n));

    return w;
}

QSize CardLayout::sizeHint() const
{
    QSize s(0,0);
    int n = list.count();
    if (n > 0)
        s = QSize(100,70); //start with a nice default size
    int i = 0;
    while (i < n) {
        QLayoutItem *o = list.at(i);
        s = s.expandedTo(o->sizeHint());
        ++i;
    }

    int h = this->itemCountH();
    int w = this->itemCountV();

    s.setHeight(h * s.height());
    s.setWidth( w * s.width());

    return s + QSize(w*spacing(), h*spacing());
}

QSize CardLayout::minimumSize() const
{
    QSize s(0,0);
    int n = list.count();
    int i = 0;
    while (i < n) {
        QLayoutItem *o = list.at(i);
        s = s.expandedTo(o->minimumSize());
        ++i;
    }

    int h = this->itemCountH();
    int w = this->itemCountV();

    s.setHeight(h * s.height());
    s.setWidth( w * s.width());

    return s + QSize(w*spacing(), h*spacing());
}
