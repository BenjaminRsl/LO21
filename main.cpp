#include <QApplication>
#include "mainwindow.h"
#include<QLabel>
#include <QPixmap>

int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    FenetrePrincipale a;
    QLabel *beta = new QLabel(&a);

    beta->move(350,100);
    beta->setPixmap(QPixmap(":/image.webp"));

    a.show();

    return app.exec();

}
