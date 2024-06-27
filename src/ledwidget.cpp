#include "ledwidget.h"

LedWidget::LedWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);

    stateLabel = new QLabel(tr("Robot state:"), this);
    stateLabel->setStyleSheet("font-weight: bold; color: red");
    stateLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(stateLabel, 0, Qt::AlignLeft);

    for (int i = 0; i < 5; ++i) {
        QHBoxLayout *ledLayout = new QHBoxLayout;

        QLabel *ledDisplay = new QLabel(this);
        ledDisplay->setFixedSize(20, 20);
        ledDisplay->setStyleSheet("background-color: gray; border-radius: 10px;");
        ledDisplays_.append(ledDisplay);

        QLabel *ledLabel = new QLabel(tr("Label"), this);
        ledLabels_.append(ledLabel);

        ledLayout->addWidget(ledDisplay);
        ledLayout->addWidget(ledLabel);
        mainLayout->addLayout(ledLayout);
    }
    setLayout(mainLayout);
    setLedNames();



    this->setAutoFillBackground(true);
    this->setPalette(pal);

}
void LedWidget::setFlags(uint8_t flags) {
    flags_ = flags;
    updateLedDisplays();
}

void LedWidget::setLedNames() {
    stateLabel->setText(tr("Robot state:"));
    ledLabels_[0]->setText(tr("Connection"));
    ledLabels_[1]->setText(tr("Stopped"));
    ledLabels_[2]->setText(tr("Manual mode"));
    ledLabels_[3]->setText(tr("Automatic mode"));
    ledLabels_[4]->setText(tr("Obstacle detected"));
}

void LedWidget::updateLedDisplays() {
    for (int i = 0; i < 5; ++i) {
        if (flags_ & (1 << i)) {
            ledDisplays_[i]->setStyleSheet("background-color: green; border-radius: 10px;");
        } else {
            ledDisplays_[i]->setStyleSheet("background-color: gray; border-radius: 10px;");
        }
    }
}
