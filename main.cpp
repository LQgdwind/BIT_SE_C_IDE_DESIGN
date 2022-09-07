#include "mainwindow.h"
#include <QApplication>
#include "helper.h"
#include "etheme.h"
ETheme::THEME ETheme::curTheme=ETheme::black;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QStringLiteral("QEditor"));
    w.setStyleSheet("background-color: rgb(60,60,60);color: rgb(160,160,160)");
    w.show();
    return a.exec();
}
