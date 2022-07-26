#include "DigitalEarth.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DigitalEarth w;
    w.show();
    return a.exec();
}
