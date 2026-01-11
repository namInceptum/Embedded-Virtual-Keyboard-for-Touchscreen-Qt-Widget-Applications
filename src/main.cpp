/**
 *  MIT License
 *  Copyright (c) BOMKE; florisa
 *  See accompanying LICENSE file
 */

 #include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
