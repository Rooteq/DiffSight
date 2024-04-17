#ifndef CONTROLKEYS_H
#define CONTROLKEYS_H

#include <QWidget>
#include <QtWidgets>
#include <QPushButton>

class ControlKeys : public QWidget{
 Q_OBJECT
public:
    ControlKeys(QWidget *parent = nullptr) : QWidget(parent){
        upButton = new QPushButton("↑", this);
        downButton = new QPushButton("↓", this);
        leftButton = new QPushButton("←", this);
        rightButton = new QPushButton("→", this);

        connect(upButton, SIGNAL(pressed()), this, SLOT(forwardClicked()));
        connect(upButton, SIGNAL(released()), this, SLOT(unclicked()));

        upButton->setFixedSize(50, 50);
        leftButton->setFixedSize(50, 50);
        downButton->setFixedSize(50, 50);
        rightButton->setFixedSize(50, 50);

        QGridLayout* layout = new QGridLayout(this);
        // Adjusting button size
        QFont font = upButton->font();
        font.setPointSize(16); // You can adjust the font size as needed
        upButton->setFont(font);
        leftButton->setFont(font);
        downButton->setFont(font);
        rightButton->setFont(font);

        // Making buttons square


        // Adding buttons to layout
        layout->addWidget(upButton, 0, 1, 1, 1, Qt::AlignCenter);
        layout->addWidget(leftButton, 1, 0);
        layout->addWidget(downButton, 1, 1, 1, 1, Qt::AlignCenter);
        layout->addWidget(rightButton, 1, 2);


        // Centering the layout
        layout->setColumnStretch( 0, 0 ) ; // Give column 0 no stretch ability
        layout->setRowStretch(0,0);
        layout->setHorizontalSpacing(5);
        layout->setVerticalSpacing(5);

        layout->setContentsMargins(0, 0, 0, 0);

        setLayout(layout);
    }
public slots:
    void forwardClicked()
    {
        emit goForward();
    }
    void unclicked()
    {
        emit stop();
    }
signals:
    void goForward();
    void stop();
private:
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* leftButton;
    QPushButton* rightButton;
};

#endif // CONTROLKEYS_H
