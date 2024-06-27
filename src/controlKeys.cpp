#include "controlKeys.h"

ControlKeys::ControlKeys(QWidget *parent) : QWidget(parent) {
    // Create buttons
    upButton = new QPushButton("↑", this);
    downButton = new QPushButton("↓", this);
    leftButton = new QPushButton("←", this);
    rightButton = new QPushButton("→", this);

    // Connect signals and slots
    connect(upButton, SIGNAL(pressed()), this, SLOT(forwardClicked()));
    connect(downButton, SIGNAL(pressed()), this, SLOT(backwardClicked()));
    connect(leftButton, SIGNAL(pressed()), this, SLOT(leftClicked()));
    connect(rightButton, SIGNAL(pressed()), this, SLOT(rightClicked()));


    connect(upButton, SIGNAL(released()), this, SLOT(unclicked()));
    connect(downButton, SIGNAL(released()), this, SLOT(unclicked()));
    connect(leftButton, SIGNAL(released()), this, SLOT(unclicked()));
    connect(rightButton, SIGNAL(released()), this, SLOT(unclicked()));

    // Set fixed size for buttons
    upButton->setFixedSize(50, 50);
    leftButton->setFixedSize(50, 50);
    downButton->setFixedSize(50, 50);
    rightButton->setFixedSize(50, 50);

    // Create grid layout
    QGridLayout* layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    // Adjust font size
    QFont font = upButton->font();
    font.setPointSize(16);
    upButton->setFont(font);
    leftButton->setFont(font);
    downButton->setFont(font);
    rightButton->setFont(font);

    // Add buttons to layout
    layout->addWidget(upButton, 0, 1);
    layout->addWidget(leftButton, 1, 0);
    layout->addWidget(downButton, 1, 1);
    layout->addWidget(rightButton, 1, 2);

    // Set the size policy of the widget containing the layout to Fixed
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Set layout
    setLayout(layout);
}
