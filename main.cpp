/**
 * @file main.cpp
 * @author Szymon
 * @brief Main file contains the main QApplication and MainWindow objects - compulsory for displaying the main window
 * @version 0.1
 * @date 2024-04-23
 * 
 * 
 */

#include <QKeyEvent>

#include "mainwindow.h"

#include <QMatrix3x3>
#include <QTimer>

/**
 * @brief Main function
 * MainWindow is responsible for application logic and looks
 */
int main(int argc, char *argv[])
{
    QApplication App(argc, argv);
    MainWindow window;
    window.show();

    return App.exec();
}
