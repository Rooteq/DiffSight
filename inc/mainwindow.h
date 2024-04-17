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
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent)
    {
        server = new DataServer;

        graphicsView = new GraphicsView(this);
        //setCentralWidget(graphicsView);

        keys = new ControlKeys(this);

        // here make a funtion to create window maybe? As per Kretchmehr's instructions
        //QPushButton* button = new QPushButton("elo", this);

        connect(keys, SIGNAL(goForward()), this, SLOT(onClick()));
        connect(keys, SIGNAL(stop()), this, SLOT(onRelease()));

        // connect(button, &QPushButton::pressed, this, &MainWindow::onClick);
        // connect(button, &QPushButton::released, this, &MainWindow::onRelease);

        QHBoxLayout* layout = new QHBoxLayout;
        layout->addWidget(graphicsView);
        layout->addWidget(keys);

        QWidget* centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);

        setCentralWidget(centralWidget);

    }

public slots:
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
    ControlKeys* keys;
    DataServer* server;
};
#endif // MAINWINDOW_H
