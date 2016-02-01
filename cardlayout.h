#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

#include <QLayout>
#include <QList>

class CardLayout : public QLayout
{
public:
    CardLayout(QWidget *parent);
    CardLayout();
    ~CardLayout();

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    void setGeometry(const QRect &rect);

protected:
    QList<QLayoutItem*> list;

    int itemCountH() const;
    int itemCountV() const;
};

#endif // CARDLAYOUT_H
