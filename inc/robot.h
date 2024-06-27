/**
 * @file robot.h
 * @brief Main robot class for representing and managing the robot's state and position.
 *
 * This file contains the declaration of the Robot class, which manages the robot's graphical representation
 * and its position within a scene.
 *
 * @version 0.1
 *
 * @author Szymon
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <QVector3D>
#include <QGraphicsScene>
#include <QtMath>

#include "robotdrawing.h"

/**
 * @class Robot
 * @brief The Robot class represents the robot and manages its state and position.
 *
 * This class handles the robot's graphical representation and provides methods to update and retrieve
 * its position and orientation.
 */
class Robot {
public:
    /**
     * @brief Construct a new Robot object.
     *
     * Initializes the robot with a default position and graphical representation.
     */
    Robot();

    /**
     * @brief Get the robot's angle.
     *
     * @return Reference to the robot's angle.
     */
    double& getAngle() { return angle; }

    /**
     * @brief Get the robot's x-coordinate.
     *
     * @return Reference to the robot's x-coordinate.
     */
    double& getX() { return x; }

    /**
     * @brief Get the robot's y-coordinate.
     *
     * @return Reference to the robot's y-coordinate.
     */
    double& getY() { return y; }

    /**
     * @brief Get the robot's current position as a QPointF.
     *
     * @return The robot's current position.
     */
    QPointF getPos() const { return pos; }

    /**
     * @brief Get the robot's last position as a QPointF.
     *
     * @return Reference to the robot's last position.
     */
    QPointF& getLastPos() { return lastPos; }

    /**
     * @brief Get the robot's graphical entity.
     *
     * @return Pointer to the QGraphicsItemGroup representing the robot.
     */
    QGraphicsItemGroup* getRobotEntity() { return robotEntity; }

    /**
     * @brief Set the robot's position and angle.
     *
     * This function updates the robot's position and angle, and adjusts its graphical representation accordingly.
     *
     * @param[in] x - The new x-coordinate of the robot.
     * @param[in] y - The new y-coordinate of the robot.
     * @param[in] ang - The new angle of the robot.
     */
    void setPosition(int16_t x, int16_t y, int16_t ang);

private:
    QGraphicsItemGroup* robotEntity; /**< Graphical representation of the robot. */
    double angle{0};                 /**< The robot's angle. */
    double v{0};                     /**< The robot's velocity (not used currently). */
    double x{0};                     /**< The robot's x-coordinate. */
    double y{0};                     /**< The robot's y-coordinate. */

    QPointF pos;                     /**< The robot's current position. */
    QPointF lastPos;                 /**< The robot's last position. */
};

#endif // ROBOT_H
