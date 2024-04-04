//#include "mainwindow.h"


#include <QKeyEvent>

#include "mainwindow.h"

#include <QMatrix3x3>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return a.exec();
}
