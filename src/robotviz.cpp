#include "robotviz.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QRandomGenerator>

RobotViz::RobotViz(QWidget *parent)
    : QWidget(parent),
        photoLabel(new QLabel(this)),
        leftProgressBar(new QProgressBar(this)),
        rightProgressBar(new QProgressBar(this)),
        leftLabel(new QLabel("0\nRPM", this)),
        rightLabel(new QLabel("0\nRPM", this)),
        warningLabel(new QLabel(this)),
        showWarning(false) // Initialize warning flag
    {

    QPixmap photo(":/resources/res/robot.PNG");
    photoLabel->setPixmap(photo.scaled(100, 100, Qt::KeepAspectRatio));

    int progressBarWidth = 50;

    leftProgressBar->setOrientation(Qt::Vertical);
    leftProgressBar->setFixedHeight(40);
    leftProgressBar->setRange(0, 20);


    rightProgressBar->setOrientation(Qt::Vertical);
    rightProgressBar->setFixedHeight(40);
    rightProgressBar->setRange(0, 20);

    leftProgressBar->setTextVisible(false);
    rightProgressBar->setTextVisible(false);

    QString progressBarStyle = R"(
        QProgressBar {
            border: 1px solid black;
            background: white;
        }
        QProgressBar::chunk {
            background-color: green;
        }
    )";
    leftProgressBar->setStyleSheet(progressBarStyle);
    rightProgressBar->setStyleSheet(progressBarStyle);

    leftProgressBar->setStyleSheet(progressBarStyle);
    rightProgressBar->setStyleSheet(progressBarStyle);

    QWidget *leftContainer = new QWidget(this);
    QVBoxLayout *leftContainerLayout = new QVBoxLayout(leftContainer);
    QSpacerItem *leftSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *leftSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftContainerLayout->addItem(leftSpacerTop);
    leftContainerLayout->addWidget(leftProgressBar);
    leftContainerLayout->addWidget(leftLabel);
    leftContainerLayout->addItem(leftSpacerBottom);
    leftContainer->setFixedWidth(progressBarWidth);

    QWidget *rightContainer = new QWidget(this);
    QVBoxLayout *rightContainerLayout = new QVBoxLayout(rightContainer);
    QSpacerItem *rightSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *rightSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    rightContainerLayout->addItem(rightSpacerTop);
    rightContainerLayout->addWidget(rightProgressBar);
    rightContainerLayout->addWidget(rightLabel);
    rightContainerLayout->addItem(rightSpacerBottom);
    rightContainer->setFixedWidth(progressBarWidth);

    warningLabel->setStyleSheet("QLabel { background-color : red; color : white; }");
    warningLabel->setAlignment(Qt::AlignCenter);
    warningLabel->setFixedHeight(25);
    warningLabel->setVisible(false);

    QVBoxLayout *photoAndWarningLayout = new QVBoxLayout;
    photoAndWarningLayout->addWidget(warningLabel);
    photoAndWarningLayout->addWidget(photoLabel);

    QSpacerItem *leftSpacer = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem *rightSpacer = new QSpacerItem(20, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addItem(leftSpacer);
    mainLayout->addWidget(leftContainer, 0, Qt::AlignVCenter);
    mainLayout->addLayout(photoAndWarningLayout, 0);
    mainLayout->addWidget(rightContainer, 0, Qt::AlignVCenter);
    mainLayout->addItem(rightSpacer);

    setLayout(mainLayout);
}

void RobotViz::setParams(const int8_t rpmL, const int8_t rpmR, const uint8_t flag, const int16_t distanceToObstacle)
{
    int leftValue = std::clamp(static_cast<int>(rpmL), 0, 100);
    int rightValue = std::clamp(static_cast<int>(rpmR), 0, 100);

    leftProgressBar->setValue(leftValue);
    rightProgressBar->setValue(rightValue);

    leftLabel->setText(QString::number(leftValue) + "\nRPM");
    rightLabel->setText(QString::number(rightValue) + "\nRPM");

    if((flag & 0x10) == 0)
        warningLabel->setVisible(false);
    else
    {
        warningLabel->setVisible(true);
        warningLabel->setText(QString::number(distanceToObstacle) + "cm");
    }
}
