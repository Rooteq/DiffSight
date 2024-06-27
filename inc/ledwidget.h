/**
 * @file ledwidget.h
 * @brief LED status display widget
 * @version 0.1
 *
 * @details This file contains the declaration of the LedWidget class, which is used
 * to display the status of various system indicators using LED representations.
 *
 *
 */

#ifndef LEDWIDGET_H
#define LEDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>

/**
 * @class LedWidget
 * @brief A widget that displays the status of various indicators using LED representations.
 *
 * The LedWidget class manages a set of LEDs that indicate the status of different system parameters.
 * Each LED is accompanied by a label that describes the parameter it represents.
 */
class LedWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Constructs a new LedWidget object.
     * @param[in] parent - The parent widget.
     */
    explicit LedWidget(QWidget *parent = nullptr);

    /**
     * @brief Sets the flags that determine which LEDs are lit.
     * @param[in] flags - A bitmask representing the LED statuses.
     */
    void setFlags(uint8_t flags);

    /**
     * @brief Sets the names of the LEDs.
     *
     * This method sets the text labels for each of the LEDs to describe what each LED represents.
     */
    void setLedNames();
protected:
    /**
     * @brief Updates the LED displays based on the current flags.
     *
     * This method updates the color of each LED based on the corresponding bit in the flags_ member variable.
     */
    void updateLedDisplays();
private:
    uint8_t flags_ = 0;                 ///< A bitmask representing the current LED statuses.
    QVector<QLabel*> ledLabels_;        ///< A vector of labels for the LEDs.
    QVector<QLabel*> ledDisplays_;      ///< A vector of QLabel objects representing the LEDs.
    QLabel *stateLabel;                 ///< A label with robot state text.
};

#endif // LEDWIDGET_H
