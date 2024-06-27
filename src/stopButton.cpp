#include <stopButton.h>

StopButton::StopButton(QWidget *parent)
    : QWidget(parent)
{
    stopButton = new QPushButton("STOP", this);

    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopClicked()));

    stopButton->setFixedSize(50, 50);
    stopButton->setStyleSheet("QPushButton {"
                              "border-radius: 25px;"
                              "background-color: #FF0000;"
                              "color: white;"
                              "border: none;"
                              "}"
                              "QPushButton:hover {"
                              "background-color: #E00000;"
                              "}");
}
