#include "cardwidget.h"

#include "adjustablelayout.h"
#include "cardlayout.h"

//#include <QGridLayout>


CardWidget::CardWidget(QWidget *parent) : QWidget(parent)
{
    AdjustableLayout* l = new AdjustableLayout(this);
    l->setColumn(5);

    l->setSpacing(0);
}
