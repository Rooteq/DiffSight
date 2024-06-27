#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    linesIndex = 0;
    dotsIndex = 0;
    lines.resize(LINES_SEGMENTS);
    dots.resize(NUM_DOTS);

    for(auto& iter : lines)
        iter = nullptr;

    for(auto& iter : dots)
        iter = nullptr;

    scene = new QGraphicsScene(this);
    robot = new Robot();

    for (int x=-1500; x<=1500; x+=100)
        scene->addLine(x,-1500,x,1500, QPen(Qt::lightGray));

    for (int y=-1500; y<=1500; y+=100)
        scene->addLine(-1500,y,1500,y, QPen(Qt::lightGray));

    scene->addItem(robot->getRobotEntity());
    singleItem = robot->getRobotEntity();

    setScene(scene);

    qreal sceneWidth = 1000;
    qreal sceneHeight = 1000;
    qreal sceneCenterX = sceneWidth / 2.0;
    qreal sceneCenterY = sceneHeight / 2.0;
    qreal sceneMargin = 50;

    setSceneRect(-sceneCenterX - sceneMargin, -sceneCenterY - sceneMargin, sceneWidth + 2 * sceneMargin, sceneHeight + 2 * sceneMargin);
    robot->getLastPos() = QPointF(0,0);

    currentDestinationCross = nullptr;
}

void GraphicsView::drawCross(QPointF pos)
{
    if(currentDestinationCross != nullptr)
        scene->removeItem(currentDestinationCross);

    currentDestinationCross = new CrossItem(QPointF(pos.x(),-pos.y()));
    scene->addItem(currentDestinationCross);
}

void GraphicsView::drawObstacles(const uint8_t flag, int16_t distanceToObstacle)
{
    if((flag & 0x10) == 0)
        return;

    distanceToObstacle *= 10;
    distanceToObstacle += 77;

    int xo = robot->getPos().x() + distanceToObstacle * cos(qDegreesToRadians(-robot->getAngle()));
    int yo = robot->getPos().y() - distanceToObstacle * sin(qDegreesToRadians(-robot->getAngle()));

    scene->addItem(new DotObject(QPointF(xo,yo)));


    if(dots[dotsIndex] == nullptr)
    {
        dots[dotsIndex] = new DotObject(QPointF(xo,yo));
        scene->addItem(dots[dotsIndex]);
    }
    else
    {
        scene->removeItem(dots[dotsIndex]);
        delete dots[dotsIndex];
        dots[dotsIndex] = new DotObject(QPointF(xo,yo));
        scene->addItem(dots[dotsIndex]);
    }
    dotsIndex = (dotsIndex + 1) % NUM_DOTS;
}

void GraphicsView::updateRobotPosition(const int16_t x, const int16_t y, const int16_t ang)
{
    robot->setPosition(x,-y,ang);
    singleItem->setPos(robot->getPos());
    singleItem->setRotation(-ang);

    if(robot->getLastPos() != robot->getPos()) // dont insert when stationary
    {
        if(lines[linesIndex] == nullptr)
        {
            lines[linesIndex] = new LineItem(robot->getLastPos(),robot->getPos());
            scene->addItem(lines[linesIndex]);
        }
        else
        {
            scene->removeItem(lines[linesIndex]);
            delete lines[linesIndex];
            lines[linesIndex] = new LineItem(robot->getLastPos(),robot->getPos());
            scene->addItem(lines[linesIndex]);
        }
        linesIndex = (linesIndex + 1) % LINES_SEGMENTS;
    }
}

void GraphicsView::recalculatePositionToObstacles(const int16_t x, const int16_t y)
{
    if(dots.empty()) return;
    for(auto& dot:dots)
    {
        if(dot == nullptr) break;
        float distance = qSqrt(qPow((x - dot->pos().x()), 2) + qPow((y - dot->pos().y()), 2));

        float rValue = (distance - 100);

        if(rValue > 255)
                rValue = 255;
        if(rValue < 0)
                rValue = 0;

        dot->setColor(QColor::fromRgb(255 - rValue, 0, 255, 255));
        dot->update();
    }
}

void GraphicsView::updateScene()
{
    singleItem->setPos(robot->getPos());
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        return;
    }

    if (!event->isAutoRepeat())
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if(ke->key() == Qt::Key_Up)
            emit upPressed();
        if(ke->key() == Qt::Key_Left)
            emit leftPressed();
        if(ke->key() == Qt::Key_Right)
            emit rightPressed();
        if(ke->key() == Qt::Key_Down)
            emit downPressed();
        if(ke->key() == Qt::Key_Space)
            emit stopPressed();
    }
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
    {
        return;
    }

    QKeyEvent *ke = static_cast<QKeyEvent *>(event);

    if(ke->key() == Qt::Key_Up)
        emit stopPressed();
    if(ke->key() == Qt::Key_Left)
        emit stopPressed();
    if(ke->key() == Qt::Key_Right)
        emit stopPressed();
    if(ke->key() == Qt::Key_Down)
        emit stopPressed();
}
