
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QTGUIExampleModel m;
    w.setModel(m);
    w.show();

    return a.exec();
}


