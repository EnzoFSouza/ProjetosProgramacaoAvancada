#include "mainplotador.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainPlotador w;
    w.show();
    return a.exec();
}
