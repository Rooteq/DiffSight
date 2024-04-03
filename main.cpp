//#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>

#include <QKeyEvent>

#include "robot.h"
#include "tcpserver.h"

#include <QPushButton>
#include <QVector3D>
#include <QMatrix3x3>
#include <QTimer>
#include <QtWidgets>
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
        server = new DataServer;

        graphicsView = new GraphicsView(this);
        setCentralWidget(graphicsView);


        // here make a funtion to create window maybe? As per Kretchmehr's instructions
        QPushButton* button = new QPushButton("elo", this);

        connect(button, &QPushButton::pressed, this, &MainWindow::onClick);
        connect(button, &QPushButton::released, this, &MainWindow::onRelease);

        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(graphicsView);
        layout->addWidget(button);

        QWidget* centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);

    }

private slots:
    void onClick()
    {
        server->sendMessage(QString("MP"));
        qDebug() << "Button clicked";
    }

    void onRelease()
    {
        server->sendMessage(QString("S"));
        qDebug() << "Button released";
    }

private:
    GraphicsView* graphicsView;
    DataServer* server;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

    return a.exec();
}
