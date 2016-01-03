#include "cardwidget.h"

#include <QGridLayout>

CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);

    layout->setVerticalSpacing(0);
    layout->setHorizontalSpacing(0);

}
