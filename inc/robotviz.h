/**
 * @file robotdrawing.h
 * @author Szymon
 * @brief Makes a robot top down view with motor speed and nearest obstacle distance.
 * @version 0.1
 *
 *
 */

#ifndef ROBOTVIZ_H
#define ROBOTVIZ_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>

/**
 * @class RobotViz
 * @brief This class is responsible for creating a robot top down view with motor and obstacle stats.
 *
 * This class handles the robot's top down view representation with motor speed and nearest obstacle distance.
 */
class RobotViz : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new RobotViz object.
     *
     * Places the robot top down view image, creates scaled progress bars and lables. The progress bars are scaled to 20 RPM.
     *
     * @param[in] parent - The parent widget, if any.
     */
    explicit RobotViz(QWidget *parent = nullptr);

    /**
     * @brief Sets current motor and obstacle params.
     *
     * Updates the params for the progress bars and obstacle indicator.
     *
     * @param[in] rpmL - left motor RPM.
     * @param[in] rpmR - right motor RPM.
     * @param[in] flag - robot state flag.
     * @param[in] distanceToObstacle - distance to nearest obstacle in cm.
     */
    void setParams(const int8_t rpmL, const int8_t rpmR, const uint8_t flag, const int16_t distanceToObstacle);

private:
    QLabel *photoLabel;             ///< Label for photo placement.
    QProgressBar *leftProgressBar;  ///< Left progress bar.
    QProgressBar *rightProgressBar; ///< Right progress bar.
    QLabel *leftLabel;              ///< Left engine's label for displaying rpm.
    QLabel *rightLabel;             ///< Right engine's label for displaying rpm.
    QLabel *warningLabel;           ///< Label for displaying obstacle warning and distance to obstacle.
    bool showWarning;               ///< Should the warning label be shown.
};

#endif // ROBOTVIZ_H
