#include "mainwindow.h"

#include <QApplication>

#include <QKeyEvent>

#include "robot.h"

#include <QVector3D>
#include <QMatrix3x3>
#include <QTimer>

constexpr int dt = 25;

class GraphicsView : public QGraphicsView {
public:
    GraphicsView(Robot* robot = nullptr, QWidget *parent = nullptr) : robot(robot), QGraphicsView(parent)
    {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GraphicsView::updateOnLoop);
        singleItem = robot->getRobotEntity();
        timer->start(dt);
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
    QTimer* timer;
    QGraphicsItemGroup *singleItem;
    Robot* robot;
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene scene(0,0,340,280);

    Robot* robot= new Robot(scene);

    GraphicsView view(robot);

    view.setScene(&scene);
    view.setSceneRect(-200, -200, 400, 400);

    view.show();

    // QVector3D vec(1,2,3);
    // QGenericMatrix<3,3,int> A;
    // QGenericMatrix<1,3,int> B;
    // A.fill(1);
    // B(0,0) = 1;
    // B(1,0) = 2;
    // B(2,0) = 3;

    //MainWindow w;
    // w.show();
    return a.exec();
}
