//#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>

#include <QKeyEvent>

#include "robot.h"

#include <QVector3D>
#include <QMatrix3x3>
#include <QTimer>

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
        setSceneRect(-200, -200, 400, 400);
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

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent)
    {
        graphicsView = new GraphicsView(this);
        setCentralWidget(graphicsView);
    }
private:
    GraphicsView* graphicsView;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return a.exec();
}
