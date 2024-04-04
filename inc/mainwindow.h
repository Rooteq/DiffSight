#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QMainWindow>
#include <QApplication>

#include <QPushButton>
#include <QVector3D>

#include "tcpserver.h"
#include "graphicsview.h"

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
#endif // MAINWINDOW_H
