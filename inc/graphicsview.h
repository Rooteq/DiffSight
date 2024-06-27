/**
 * @file graphicsview.h
 * @brief GraphicsView class
 *
 * This file contains the declaration of the GraphicsView class, which provides a graphical representation
 * of the robot and its environment. It includes functionalities to update the robot's position, draw destination
 * markers, and display obstacles.
 *
 * @version 0.1
 *
 */

#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>
#include <QTimer>
#include <vector>
#include "robot.h"
#include "graphicsUtils.h"

/**
 * @class GraphicsView
 * @brief The GraphicsView class provides a graphical representation of the robot and its environment.
 *
 * The GraphicsView class extends QGraphicsView to display the robot's position, path, and obstacles in a scene.
 * It allows for updating the robot's position, drawing destination crosses, and displaying obstacles detected by the robot.
 */
class GraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    /**
     * @brief Construct a new GraphicsView object.
     *
     * Initializes the graphics view, sets up the scene, and adds the robot item.
     *
     * @param[in] parent - The parent widget, if any.
     */
    GraphicsView(QWidget *parent = nullptr);

    /**
     * @brief Updates the robot's position and angle in the scene.
     *
     * This function updates the position and angle of the robot within the scene. It also handles drawing
     * lines that represent the path taken by the robot.
     *
     * @param[in] x - The new x-coordinate of the robot.
     * @param[in] y - The new y-coordinate of the robot.
     * @param[in] ang - The new angle of the robot.
     */
    void updateRobotPosition(const int16_t x, const int16_t y, const int16_t ang);

    /**
     * @brief Draws a cross at the specified position.
     *
     * This function draws a cross at the given position within the scene. If a cross already exists,
     * it removes the previous cross before adding the new one.
     *
     * @param[in] pos - The position where the cross should be drawn.
     */
    void drawCross(QPointF pos);

    /**
     * @brief Draws obstacles based on the robot's position and distance to the obstacle.
     *
     * This function adds obstacle items to the scene based on the provided flag and distance to the obstacle.
     * The dots are encapsulated in circular vector so that there aren't too many dots.
     *
     * @param[in] flag - The flag indicating the presence of an obstacle.
     * @param[in] distanceToObstacle - The distance to the obstacle.
     */
    void drawObstacles(const uint8_t flag, int16_t distanceToObstacle);

    /**
     * @brief Gets the robot's current position.
     *
     * @return The current position of the robot.
     */
    QPointF getRobotPosition() { return robot->getPos(); }

    /**
     * @brief Implements key pressed for robot movement.
     *
     * @param[in] event - The key event.
     */
    virtual void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Implements key releases for stopping the robot.
     *
     * Every key release event gets interpreted as a stop.
     *
     * @param[in] event - The key event.
     */
    virtual void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * @brief Changes color of the obstacles dots.
     *
     * Sets the color for the dot depending on how far it is from the robot.
     *
     * @param[in] x - The robot's x position.
     * @param[in] y - The robot's y position.
     */
    void recalculatePositionToObstacles(const int16_t x, const int16_t y);

signals:
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void stopPressed();

protected:
    /**
     * @brief Updates the scene.
     *
     * This function updates the scene by setting the robot's current position.
     */
    void updateScene();

private:
    QGraphicsScene* scene;                /**< The scene containing all graphical items. */
    QTimer* timer;                        /**< The timer for scene updates. */
    QGraphicsItemGroup *singleItem;       /**< The graphical item representing the robot. */
    Robot* robot;                         /**< The robot object. */
    CrossItem* currentDestinationCross;   /**< The current destination cross item. */
    std::vector<LineItem*> lines;         /**< The vector of line items representing the robot's path. */
    std::vector<DotObject*> dots;         /**< The vector of dot items representing the obstacles. */
    unsigned int linesIndex;              /**< The index for managing the lines vector. */
    unsigned int dotsIndex;               /**< The index for managing the dots vector. */
};

#endif // GRAPHICSVIEW_H
