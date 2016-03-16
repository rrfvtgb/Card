#include "windowcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowController c;
    c.load();

    QApplication::setApplicationDisplayName("Mana Flow");
    QApplication::setApplicationName("Mana Flow");

#ifndef BUILD_ID
    QApplication::setApplicationVersion("0.0.1");
#else
    QApplication::setApplicationVersion(QString("0.0.") + QString::number(BUILD_ID));
#endif

    return a.exec();
}
