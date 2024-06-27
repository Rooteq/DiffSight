/**
 * @file controlKeys.h
 * @brief ControlKeys class for handling directional control inputs
 * @version 0.1
 *
 * @details This class provides a widget with four directional buttons
 *          for controlling a robot. The buttons are up, down, left,
 *          and right arrows.
 *
 * @license Copyright (c) 2024
 *
 */

#ifndef CONTROLKEYS_H
#define CONTROLKEYS_H

#include <QWidget>
#include <QtWidgets>
#include <QPushButton>

/**
 * @class ControlKeys
 * @brief A widget containing directional control buttons for a robot.
 *
 * The ControlKeys class provides a simple user interface for controlling
 * the movement of a robot with directional buttons (up, down, left, right).
 * Signals are emitted when buttons are pressed or released to indicate
 * the desired direction of movement.
 */
class ControlKeys : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Construct a new ControlKeys object
     *
     * @param[in] parent - Pointer to the parent widget, default is nullptr
     */
    ControlKeys(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Slot for handling forward button press
     *
     * Emits the goForward() signal.
     */
    void forwardClicked() { emit goForward(); }

    /**
     * @brief Slot for handling backward button press
     *
     * Emits the goBackward() signal.
     */
    void backwardClicked() { emit goBackward(); }

    /**
     * @brief Slot for handling left button press
     *
     * Emits the goLeft() signal.
     */
    void leftClicked() { emit goLeft(); }

    /**
     * @brief Slot for handling right button press
     *
     * Emits the goRight() signal.
     */
    void rightClicked() { emit goRight(); }

    /**
     * @brief Slot for handling button release
     *
     * Emits the stop() signal.
     */
    void unclicked() { emit stop(); }

signals:
    /**
     * @brief Signal emitted when the forward button is pressed
     */
    void goForward();

    /**
     * @brief Signal emitted when the backward button is pressed
     */
    void goBackward();

    /**
     * @brief Signal emitted when the left button is pressed
     */
    void goLeft();

    /**
     * @brief Signal emitted when the right button is pressed
     */
    void goRight();

    /**
     * @brief Signal emitted when any button is released
     */
    void stop();

private:
    QPushButton* upButton;    ///< Button for moving forward
    QPushButton* downButton;  ///< Button for moving backward
    QPushButton* leftButton;  ///< Button for turning left
    QPushButton* rightButton; ///< Button for turning right
};

#endif // CONTROLKEYS_H
