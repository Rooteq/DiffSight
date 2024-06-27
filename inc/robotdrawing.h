/**
 * @file robotdrawing.h
 * @author Szymon
 * @brief Creates robot's graphical representation
 * @version 0.1
 * 
 * 
 */

#ifndef ROBOTDRAWING_H
#define ROBOTDRAWING_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>

/**
 * @class RobotDrawing
 * @brief This class is responsible for creating robot item for further display.
 *
 * This class handles the robot's graphical representation
 */
class RobotDrawing
{
public:
    /**
     * @brief Static method for creating robot graphical representation.
     *
     * Creates and returns robot graphical item.
     *
     * @return Group of items that represent a robot.
     */
    static QGraphicsItemGroup* getRobotArrow();
};

#endif // ROBOTDRAWING_H
