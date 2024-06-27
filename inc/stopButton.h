/**
 * @file stopButton.h
 * @author Marcin
 * @brief Declaration of the StopButton class which creates a stop button widget.
 * @version 0.1
 *
 * This file declares the StopButton class, which inherits from QWidget and provides a stop button widget.
 * The stop button emits a signal when clicked.
 *
 */

#ifndef STOPBUTTON_H
#define STOPBUTTON_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>

/**
 * @class StopButton
 * @brief A QWidget subclass for creating a stop button.
 *
 * An object of this class is responsible for providing a stop button graphical object along with its functionality.
 */
class StopButton : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs a StopButton widget.
     * @param[in] parent - The parent widget (default is nullptr).
     */
    StopButton(QWidget *parent = nullptr);

public slots:
    /**
     * @brief Slot function called when the stop button is clicked.
     * Emits the stop signal.
     */
    void stopClicked() { emit stop(); }

signals:
    /**
     * @brief Signal emitted when the stop button is clicked.
     */
    void stop();

private:
    QPushButton* stopButton; /**< Pointer to the stop button widget. */
};

#endif // STOPBUTTON_H
