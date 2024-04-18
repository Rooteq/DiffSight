#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>

#include <QPushButton>
#include <QVector3D>

#include "tcpserver.h"
#include "graphicsview.h"
#include "controlKeys.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent)
    {
        server = new DataServer;

        graphicsView = new GraphicsView(this);

        keys = new ControlKeys(this);

        connect(keys, SIGNAL(goForward()), this, SLOT(onForwardClick()));
        connect(keys, SIGNAL(goBackward()), this, SLOT(onBackwardClick()));
        connect(keys, SIGNAL(goLeft()), this, SLOT(onLeftClick()));
        connect(keys, SIGNAL(goRight()), this, SLOT(onRightClick()));

        connect(keys, SIGNAL(stop()), this, SLOT(onRelease()));

        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(graphicsView);
        layout->addWidget(keys);

        QWidget* centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);

    }

public slots:
    void onForwardClick()
    {
        server->sendMessage(QString("MF"));
        qDebug() << "F clicked";
    }
    void onBackwardClick()
    {
        server->sendMessage(QString("MB"));
        qDebug() << "B clicked";
    }
    void onLeftClick()
    {
        server->sendMessage(QString("ML"));
        qDebug() << "L clicked";
    }
    void onRightClick()
    {
        server->sendMessage(QString("MR"));
        qDebug() << "R clicked";
    }
    void onRelease()
    {
        server->sendMessage(QString("S"));
        qDebug() << "Button released";
    }

private:
    GraphicsView* graphicsView;
    ControlKeys* keys;
    DataServer* server;
};
#endif // MAINWINDOW_H
