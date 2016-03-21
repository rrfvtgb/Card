#ifndef ADJUSTABLELAYOUT_H
#define ADJUSTABLELAYOUT_H

#include <QLayout>



class AdjustableLayout : public QLayout
{
    Q_OBJECT

public:
    AdjustableLayout();
    AdjustableLayout(QWidget *parent);
    ~AdjustableLayout();


    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    void setGeometry(const QRect &rect);

    int rows() const;
    void setRows(int rows);

    int column() const;
    void setColumn(int column);

protected:
    QList<QLayoutItem*> list;

    int itemCountH() const;
    int itemCountV() const;

    int _rows;
    int _column;
};

#endif // ADJUSTABLELAYOUT_H
