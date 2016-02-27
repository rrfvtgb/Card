#include "windowcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowController c;
    c.load();

    QApplication::setApplicationDisplayName("Mana Flow");
    QApplication::setApplicationName("Mana Flow");
    QApplication::setApplicationVersion("0.0.1");

    return a.exec();
}
