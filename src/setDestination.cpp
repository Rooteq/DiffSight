#include "setDestination.h"

setDestination::setDestination(QWidget *parent) 
    : QWidget(parent)
{
    title = new QLabel(this);
    title->setText(tr("Set point: "));

    coordLineEdit = new QLineEdit(this);

    startButton = new QPushButton(this);
    startButton->setText(tr("Run"));
    startButton->resize(10, 20);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(title, 0, 0);
    layout->addWidget(coordLineEdit, 1, 0, 1, 2);
    layout->addWidget(startButton, 1, 2);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &setDestination::readPoint);
}

void setDestination::changeLanguate()
{
    startButton->setText(tr("Run"));
    title->setText(tr("Set point: "));
}

void setDestination::readPoint()
{
    QString input = coordLineEdit->text();
    QStringList parts = input.split(",");
    if (parts.size() == 2)
    {
        this->x = parts[0].toInt();
        this->y = parts[1].toInt();
        qDebug() << "Correct input format";
        emit destinationReady();
    }
    else
    {
        qDebug() << "Invalid input format!";
    }
}
