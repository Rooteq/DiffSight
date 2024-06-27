#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    timer = new QElapsedTimer;
    mainTimer = new QTimer;
    mainTimer->start(4000);
    timer->start();

    server = new DataServer;
    pointTogo = new setDestination(this);

    graphicsView = new GraphicsView(this);
    graphicsView->scale(0.5,0.5);
    graphicsView->setStyleSheet("background: white; border: 1px solid black; border-radius: 15px;");

    keys = new ControlKeys(this);
    ledWidget = new LedWidget(this);

    chart = new VelocityChart(this);
    rViz = new RobotViz(this);

    connect(keys, SIGNAL(goForward()), this, SLOT(onForwardClick()));
    connect(keys, SIGNAL(goBackward()), this, SLOT(onBackwardClick()));
    connect(keys, SIGNAL(goLeft()), this, SLOT(onLeftClick()));
    connect(keys, SIGNAL(goRight()), this, SLOT(onRightClick()));

    connect(keys, SIGNAL(stop()), this, SLOT(onRelease()));

    connect(graphicsView, SIGNAL(upPressed()), this, SLOT(onForwardClick()));
    connect(graphicsView, SIGNAL(downPressed()), this, SLOT(onBackwardClick()));
    connect(graphicsView, SIGNAL(leftPressed()), this, SLOT(onLeftClick()));
    connect(graphicsView, SIGNAL(rightPressed()), this, SLOT(onRightClick()));

    connect(graphicsView, SIGNAL(stopPressed()), this, SLOT(onRelease()));

    connect(server, SIGNAL(positionReady()), this, SLOT(readPosition()));
    connect(pointTogo, SIGNAL(destinationReady()), this, SLOT(readDestination()));

    stopPush = new StopButton(this);

    stopPush->setFixedSize(50, 50);
    connect(stopPush, SIGNAL(stop()), this, SLOT(onRelease()));

    languageSelect = new Languages(this);

    connect(languageSelect, SIGNAL(languageChanged(QString)), this, SLOT(changeLanguage(QString)));
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(timeout()));

    QGridLayout* mainLayout = new QGridLayout;

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(ledWidget);
    horizontalLayout->addWidget(rViz);

    mainLayout->addWidget(graphicsView, 0, 0, 6, 5);
    mainLayout->addWidget(chart, 0, 5, 3, 4);
    mainLayout->addWidget(pointTogo, 5, 8, 1, 1);

    mainLayout->addLayout(horizontalLayout, 3,5,2,4);
    //mainLayout->addWidget(ledWidget, 4, 5, 1, 3); // changed 3 to 2
    mainLayout->addWidget(stopPush, 5, 6);
    mainLayout->addWidget(keys, 5, 5, 1, 1);

    QHBoxLayout* topBarLayout = new QHBoxLayout;
    topBarLayout->addWidget(languageSelect);
    topBarLayout->addStretch();

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addLayout(topBarLayout);
    centralLayout->addLayout(mainLayout);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

}

void MainWindow::onForwardClick()
{
    server->sendMessage(QString("MF"));
    qDebug() << "F clicked";
}
void MainWindow::onBackwardClick()
{
    server->sendMessage(QString("MB"));
    qDebug() << "B clicked";
}
void MainWindow::onLeftClick()
{
    server->sendMessage(QString("ML"));
    qDebug() << "L clicked";
}
void MainWindow::onRightClick()
{
    server->sendMessage(QString("MR"));
    qDebug() << "R clicked";
}
void MainWindow::onRelease()
{
    server->sendMessage(QString("MS"));
    qDebug() << "Button released";
}

void MainWindow::readDestination()
{
    qDebug() << "Reading destination: ";
    qDebug() << "X: " << pointTogo->getX();
    qDebug() << "Y: " << pointTogo->getY();

    server->sendPosition(pointTogo->getX(), pointTogo->getY());
    graphicsView->drawCross(QPointF(pointTogo->getX(), pointTogo->getY()));
}

void MainWindow::readPosition()
{
    qDebug() << "Reading Position:";
    qDebug() << "flag: " << server->data.flag;
    qDebug() << "X: " << server->data.x;
    qDebug() << "Y: " << server->data.y;
    qDebug() << "ang: " << server->data.ang;
    qDebug() << "obstacleProx: " << server->data.obstacleProximity;
    qDebug() << "rpmL: " << server->data.rpmL;
    qDebug() << "rpmR: " << server->data.rpmR;

    int elapsedTime = timer->restart();

    ledWidget->setFlags(server->data.flag);
    chart->update(QPointF(server->data.x, server->data.y), elapsedTime);
    graphicsView->updateRobotPosition(server->data.x, server->data.y, server->data.ang);
    graphicsView->drawObstacles(server->data.flag, server->data.obstacleProximity);

    graphicsView->recalculatePositionToObstacles(server->data.x, server->data.y);

    rViz->setParams(server->data.rpmL, server->data.rpmR, server->data.flag, server->data.obstacleProximity);

    mainTimer->start(4000);

}

void MainWindow::retranslateUi()
{
    ledWidget->setLedNames(); // for language retranslation
    pointTogo->changeLanguate();
}

void MainWindow::changeLanguage(const QString &language)
{
    if (language == "English") {
        qDebug() << "Changing to English!";
        if(!translator.load("app_en.qm"))
            qDebug() << "Error loading language file!";
    }
    else if (language == "Polski") {
        qDebug() << "Changing to Polish!";
        if(!translator.load("app_pl.qm"))
            qDebug() << "Error loading language file!";
    }
    else if (language == "Ślůnski") {
        qDebug() << "Changing to Slunski!";
        if(!translator.load("app_sl.qm"))
            qDebug() << "Error loading language file!";
    }
    qApp->installTranslator(&translator);
    retranslateUi();
}

void MainWindow::timeout() // what happens after a timeout
{
    qDebug() << "TIMEOUT";
    ledWidget->setFlags(0);
    timer->restart();
    mainTimer->start(4000);
}
