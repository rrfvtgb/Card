#include "adjustablelayout.h"

#include <QtMath>

AdjustableLayout::AdjustableLayout()
{

}

AdjustableLayout::AdjustableLayout(QWidget *parent): QLayout(parent)
{

}

AdjustableLayout::~AdjustableLayout()
{
     QLayoutItem *item;
     while ((item = takeAt(0)))
         delete item;
}

int AdjustableLayout::count() const
{
    // QList::size() returns the number of QLayoutItems in the list
    return list.size();
}

QLayoutItem *AdjustableLayout::itemAt(int idx) const
{
    // QList::value() performs index checking, and returns 0 if we are
    // outside the valid range
    return list.value(idx);
}

QLayoutItem *AdjustableLayout::takeAt(int idx)
{
    // QList::take does not do index checking
    return idx >= 0 && idx < list.size() ? list.takeAt(idx) : 0;
}

void AdjustableLayout::addItem(QLayoutItem *item)
{
    list.append(item);
}

void AdjustableLayout::setGeometry(const QRect &r)
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

int AdjustableLayout::itemCountH() const
{
    if(_rows != 0){
        return _rows;
    }

    int n = this->count();
    qreal w = qCeil(qSqrt(n));

    return qCeil(n/w);
}

int AdjustableLayout::itemCountV() const
{
    if(_column != 0){
        return _column;
    }

    int n = this->count();
    int w = qCeil(qSqrt(n));

    return w;
}

int AdjustableLayout::column() const
{
    return _column;
}

void AdjustableLayout::setColumn(int column)
{
    _column = column;
}

int AdjustableLayout::rows() const
{
    return _rows;
}

void AdjustableLayout::setRows(int rows)
{
    _rows = rows;
}

QSize AdjustableLayout::sizeHint() const
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

QSize AdjustableLayout::minimumSize() const
{
    QSize s(0,0);
    int n = list.count();
    int i = 0;

    while (i < n) {
        QLayoutItem *o = list.at(i);
        s = s.expandedTo(o->minimumSize());
        ++i;
    }

    s.setHeight(s.height() + spacing());
    s.setWidth( s.width()  + spacing());

    return s + QSize(spacing(), spacing());
}
