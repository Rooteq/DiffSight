#include "charts.h"

VelocityChart::VelocityChart(QWidget *parent)
    : QChartView(new QChart(), parent),
    m_series(new QLineSeries()),
    m_x(0)
{
    lastPosition = QPointF(0,0);

    QChart *chart = this->chart();
    chart->legend()->hide();
    chart->addSeries(m_series);

    QValueAxis *axisX = new QValueAxis;
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("t[s]");
    chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 70);
    axisY->setLabelFormat("%d");
    axisY->setTitleText("v[mm/s]");
    chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
}

VelocityChart::~VelocityChart() {
    delete m_series;
}

void VelocityChart::update(const QPointF& newPosition, const int elapsedTime)
{
    //qDebug() << "Elapsed time: " << elapsedTime;
    float velocity = (qSqrt(qPow(newPosition.x() - lastPosition.x(),2) + qPow(newPosition.y() - lastPosition.y(),2)) / elapsedTime)*1000;
    qDebug() << "Speed: " << velocity;

    m_series->append(m_x++, velocity);

    if (m_x > 100) {
        QValueAxis *axisX = static_cast<QValueAxis *>(chart()->axes(Qt::Horizontal).first());
        axisX->setRange(m_x - 100, m_x);
    }

    if (m_series->count() > 100) {
        m_series->remove(0);
    }

    lastPosition = newPosition;
}

void VelocityChart::updateChart() {
    int y = QRandomGenerator::global()->bounded(100);
    m_series->append(m_x++, y);

    if (m_x > 100) {
        QValueAxis *axisX = static_cast<QValueAxis *>(chart()->axes(Qt::Horizontal).first());
        axisX->setRange(m_x - 100, m_x);
    }

    if (m_series->count() > 100) {
        m_series->remove(0);
    }
}
