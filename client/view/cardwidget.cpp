#include "cardwidget.h"

#include "cardlayout.h"

//#include <QGridLayout>


CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
    //QGridLayout *layout = new QGridLayout(this);
    CardLayout *layout = new CardLayout(this);

    layout->setSpacing(0);
}
