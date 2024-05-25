#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;

    QSize size = w.size();
    QScreen *screen = a.screens().at(0);
    w.move((screen->size().width() - size.width()) / 2, 0);


    w.show();
    return a.exec();
}
