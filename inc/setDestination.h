/**
 * @file setDestination.h
 * @brief Declaration of the setDestination class for setting a destination point.
 * @version 0.1
 *
 * @details This file contains the declaration of the setDestination class, which is responsible
 *          for providing a user interface to set a destination point with x and y coordinates.
 *          The class allows the user to input coordinates and emits a signal when the destination
 *          is ready.
 *
 */

#ifndef SETDESTINATION_H
#define SETDESTINATION_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>

/**
 * @class setDestination
 * @brief A QWidget subclass for setting a destination point.
 *
 * This class provides a user interface that allows the user to input a destination point
 * with x and y coordinates. It includes a line edit for entering coordinates, a button to
 * confirm the input, and a label for the title. When the destination is set, the class emits
 * a signal to notify other parts of the application.
 */
class setDestination : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for setDestination.
     *
     * Initializes the widget and its components.
     *
     * @param[in] parent - Pointer to the parent widget, defaults to nullptr.
     */
    setDestination(QWidget *parent = nullptr);

    /**
     * @brief Gets the x-coordinate of the destination point.
     * @return The x-coordinate as an int16_t.
     */
    int16_t getX() const { return x; }

    /**
     * @brief Gets the y-coordinate of the destination point.
     * @return The y-coordinate as an int16_t.
     */
    int16_t getY() const { return y; }

    /**
     * @brief Changes the language of the UI elements.
     *
     * Updates the text of the button and title label based on the current language setting.
     */
    void changeLanguate();

signals:
    /**
     * @brief Signal emitted when the destination point is ready.
     */
    void destinationReady();

private slots:
    /**
     * @brief Reads the point from the input line edit.
     *
     * Parses the input text for coordinates and updates the x and y values. If the input format
     * is correct, emits the destinationReady signal.
     */
    void readPoint();

private:
    QLineEdit *coordLineEdit;  ///< Line edit for entering the coordinates.
    QPushButton *startButton;  ///< Button to confirm the coordinates.
    QLabel *title;             ///< Label for the title.

    int16_t x;  ///< x-coordinate of the destination point.
    int16_t y;  ///< y-coordinate of the destination point.
};

#endif // SETDESTINATION_H
