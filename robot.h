#ifndef ROBOT_H
#define ROBOT_H

#include <QVector3D>
#include <QGraphicsScene>
#include <QtMath>

#include "robotdrawing.h"

class Robot
{
public:
    Robot(QGraphicsScene& scene);
    double& getAngle() {return angle;}
    double& getX() {return x;}
    double& getY() {return x;}
    QPointF getPos() const {return pos;}
    QGraphicsItemGroup* getRobotEntity(){return robotEntity;}
private:
    QGraphicsItemGroup* robotEntity;
    double angle{0};
    double v{0};
    double x{0};
    double y{0};
    QPointF pos;
public slots:
    void updatePosition(const double vel, const double w,int dt)
    {
        this->v+=vel;

        double dth = w;
        angle += dth;

        double dx = cos(qDegreesToRadians(angle))*v*dt*0.01;
        double dy = sin(qDegreesToRadians(angle))*v*dt*0.01;

        x += dx;
        y += dy;

        // change coordinate system

        pos = QPointF(x,y);

        qDebug() << dx << ", " << dy;

        robotEntity->setRotation(angle);
    }

    void turn()
    {
        angle++;
    }

};

#endif // ROBOT_H
