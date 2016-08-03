#include "criusgui.h"
#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CriusGUI w;
    w.show();

    return a.exec();
}
