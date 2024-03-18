#ifndef ROBOTDRAWING_H
#define ROBOTDRAWING_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>

// virtual class for drawing a robot - anybody can implement it to draw a robot
class RobotDrawing
{
public:
    static QGraphicsItemGroup* getRobotArrow(QGraphicsScene& scene)
    {
        // Draw a circle
        int radius = 50;
        QGraphicsEllipseItem *circle = scene.addEllipse(-radius, -radius, 2 * radius, 2 * radius);

        // Draw an arrow
        QPolygonF arrowPolygon;
        arrowPolygon << QPointF(30, 0) << QPointF(-10, -10) << QPointF(-10, 10) << QPointF(30, 0);
        QGraphicsPolygonItem *arrow = scene.addPolygon(arrowPolygon);
        arrow->setBrush(Qt::black);

        QGraphicsItemGroup* robotEntity = scene.createItemGroup({circle, arrow});

        robotEntity->setPos(0,0);
        return robotEntity;
    };
};

#endif // ROBOTDRAWING_H
