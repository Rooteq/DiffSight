#include "robot.h"

Robot::Robot() : robotEntity(RobotDrawing::getRobotArrow())
{
    pos = {0,0};
}

void Robot::setPosition(int16_t x, int16_t y, int16_t ang)
{
    this->lastPos = QPointF(this->x,this->y);

    this->x = x;
    this->y = y;
    this->angle = -ang;

    pos = QPointF(this->x,this->y);
    robotEntity->setRotation(this->angle);
}
