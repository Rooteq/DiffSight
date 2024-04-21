#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>
#include <QTimer>

#include "robot.h"

constexpr int dt = 25;

class GraphicsView : public QGraphicsView {
public:
    GraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GraphicsView::updateOnLoop);
        timer->start(dt);

        scene = new QGraphicsScene(this);
        robot = new Robot(scene); // pass the pointer lolz
        singleItem = robot->getRobotEntity();
        setScene(scene);

        qreal sceneWidth = 1000; // width of scene in millimeters
        qreal sceneHeight = 1000; // height of scene in millimeters
        qreal sceneCenterX = sceneWidth / 2.0;
        qreal sceneCenterY = sceneHeight / 2.0;
        qreal sceneMargin = 50; // extra margin to add around the scene

        setSceneRect(-sceneCenterX - sceneMargin, -sceneCenterY - sceneMargin, sceneWidth + 2 * sceneMargin, sceneHeight + 2 * sceneMargin);

    }

    void updateRobotPosition(int16_t x, int16_t y, int16_t ang)
    {
        robot->setPosition(x,y,ang);
        singleItem->setPos(robot->getPos());
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        qreal v = 0, w = 0;
        switch (event->key()) {
        case Qt::Key_Left:
            w = -5;
            break;
        case Qt::Key_Right:
            w = 5;
            break;
        case Qt::Key_Up:
            v = 1;
            break;
        case Qt::Key_Down:
            v = -1;
            break;
        default:
            QGraphicsView::keyPressEvent(event);
            return;
        }
        robot->updatePosition(v,w, dt-timer->remainingTime());
        singleItem->setPos(robot->getPos());
        //qDebug() << singleItem->pos();
    }

    void updateOnLoop()
    {
        robot->updatePosition(0,0,100);
        singleItem->setPos(robot->getPos());
    }

private:
    QGraphicsScene* scene;
    QTimer* timer;
    QGraphicsItemGroup *singleItem; // this is to draw robot, change it xdd
    Robot* robot;
};




#endif // GRAPHICSVIEW_H
