#include "robot.h"

Robot::Robot(QGraphicsScene& scene) : robotEntity(RobotDrawing::getRobotArrow(scene))
{
    pos = {0,0};
}
