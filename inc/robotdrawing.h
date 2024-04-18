#ifndef ROBOTDRAWING_H
#define ROBOTDRAWING_H

#include <QGraphicsEllipseItem>
#include <QGraphicsView>

// virtual class for drawing a robot - anybody can implement it to draw a robot
class RobotDrawing
{
public:
    static QGraphicsItemGroup* getRobotArrow(QGraphicsScene* scene)
    {
        // Draw a circle
        qreal diameter = 200; // 20 cm diameter converted to mm
        QGraphicsEllipseItem *circle = scene->addEllipse(-diameter/2, -diameter/2, diameter, diameter);

        // Draw an arrow
        QPolygonF arrowPolygon;
        arrowPolygon << QPointF(75, 0) << QPointF(-45, -45) << QPointF(-45, 45) << QPointF(75, 0);
        QGraphicsPolygonItem *arrow = scene->addPolygon(arrowPolygon);
        arrow->setBrush(Qt::black);

        QGraphicsItemGroup* robotEntity = scene->createItemGroup({circle, arrow});

        robotEntity->setPos(0, 0);
        return robotEntity;
    };
};

#endif // ROBOTDRAWING_H
