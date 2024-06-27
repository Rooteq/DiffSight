/**
 * @file mainwindow.h
 * @brief Main window class - backbone of the application
 *
 * This file contains the declaration of the MainWindow class, which is the main interface of the application.
 * It handles the main window layout, user inputs, and communication with the robot via a websocket server.
 *
 * @version 0.1
 *
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>
#include <QTranslator>
#include <QPushButton>
#include <QVector3D>
#include <QTimer>
#include <robotviz.h>

#include "tcpserver.h"
#include "graphicsview.h"
#include "controlKeys.h"
#include "stopButton.h"
#include "languages.h"
#include "setDestination.h"
#include "ledwidget.h"
#include "charts.h"

/**
 * @class MainWindow
 * @brief The MainWindow class represents the main application window.
 *
 * The MainWindow class is responsible for initializing and managing the main window of the application.
 * It sets up the user interface, connects signals and slots for user interaction, and handles communication
 * with the robot through a websocket server.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Construct a new MainWindow object.
     *
     * Initializes the main window and sets up the user interface and signal-slot connections.
     *
     * @param[in] parent - The parent widget, if any.
     */
    MainWindow(QWidget* parent = nullptr);

public slots:
    /**
     * @brief Changes the application language.
     *
     * This slot is called to change the application's language. It loads the appropriate
     * translation file based on the provided language and updates the UI elements.
     *
     * @param[in] language - The language to change to.
     */
    void changeLanguage(const QString &language);

    /**
     * @brief Handles the forward button click.
     *
     * Sends a command to move the robot forward and logs the action.
     */
    void onForwardClick();

    /**
     * @brief Handles the backward button click.
     *
     * Sends a command to move the robot backward and logs the action.
     */
    void onBackwardClick();

    /**
     * @brief Handles the left button click.
     *
     * Sends a command to move the robot left and logs the action.
     */
    void onLeftClick();

    /**
     * @brief Handles the right button click.
     *
     * Sends a command to move the robot right and logs the action.
     */
    void onRightClick();

    /**
     * @brief Handles the release of movement buttons.
     *
     * Sends a command to stop the robot and logs the action.
     */
    void onRelease();

    /**
     * @brief Reads the current position of the robot.
     *
     * Retrieves the robot's current position and status from the server, updates the UI elements,
     * and logs the data.
     */
    void readPosition();

    /**
     * @brief Reads the destination coordinates.
     *
     * Retrieves the destination coordinates from the setDestination widget, sends them to the server,
     * updates the graphics view, and logs the data.
     */
    void readDestination();

    /**
     * @brief Handles timeout events.
     *
     * Resets the LED widget flags, restarts the timers, and logs the timeout event.
     */
    void timeout();

private:
    /**
     * @brief Retranslates the UI elements.
     *
     * Updates the text of UI elements to match the current language.
     */
    void retranslateUi();

    GraphicsView* graphicsView;     /**< The graphics view for displaying the simulation. */
    ControlKeys* keys;              /**< The control keys widget for arrow key inputs. */
    DataServer* server;             /**< The websocket server for communication with the robot. */
    StopButton* stopPush;           /**< The stop button widget. */
    Languages* languageSelect;      /**< The language selection widget. */
    setDestination* pointTogo;      /**< The widget for setting the destination coordinates. */
    LedWidget* ledWidget;           /**< The widget for displaying LED statuses. */
    QTranslator translator;         /**< The translator for handling multiple languages. */
    VelocityChart* chart;           /**< The chart for displaying velocity data. */
    QElapsedTimer* timer;           /**< The timer for measuring elapsed time. */
    QTimer* mainTimer;              /**< The main timer for periodic events. */

    RobotViz* rViz;
};

#endif // MAINWINDOW_H
