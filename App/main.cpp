#include "mainwindow.h"
#include <CoordinateSystem1.cpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    CoordinateSystem1 coords;
    coords.show();

    return a.exec();
}
