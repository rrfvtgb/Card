#include "windowcontroller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowController c;
    c.load();

    return a.exec();
}
