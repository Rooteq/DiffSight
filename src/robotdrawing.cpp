#include "robotdrawing.h"

QGraphicsItemGroup* RobotDrawing::getRobotArrow()
{
    QGraphicsItemGroup *robotEntity = new QGraphicsItemGroup();
    qreal diameter = 200; // 200mm is the robot's diameter

    QPen blackPen(Qt::black);
    blackPen.setWidth(4);
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(-diameter / 2, -diameter / 2, diameter, diameter);
    circle->setPen(blackPen);
    robotEntity->addToGroup(circle);

    QPolygonF arrowPolygon;
    arrowPolygon << QPointF(75, 0) << QPointF(-45, -45) << QPointF(-45, 45) << QPointF(75, 0);

    QGraphicsPolygonItem *arrow = new QGraphicsPolygonItem(arrowPolygon);
    arrow->setBrush(Qt::black);
    robotEntity->addToGroup(arrow);

    robotEntity->setPos(0, 0);
    return robotEntity;
};
