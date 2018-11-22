#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QStyleFactory::keys();
    a.setStyle(QStyleFactory::create("Fusion"));

    MainWindow w;
    //w.setStyleSheet(mainsheet.qss);
    w.show();

    return a.exec();
}
