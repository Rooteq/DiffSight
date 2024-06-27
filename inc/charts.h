/**
 * @file charts.h
 * @author Marcin
 * @brief File handling charts that show data from sensors.
 * @version 0.1
 *
 * This file defines the `VelocityChart` class, which is responsible for creating
 * and updating a chart that displays velocity data calculated from sensor inputs.
 */

#ifndef CHARTS_H
#define CHARTS_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QRandomGenerator>
#include <QPointF>
#include <QtMath>

/**
 * @class VelocityChart
 * @brief A class to display and update velocity data on a chart.
 *
 * The VelocityChart class is derived from QChartView and provides functionality
 * to display and update a line chart that shows velocity data calculated from
 * sensor inputs.
 */
class VelocityChart : public QChartView {
    Q_OBJECT
public:
    /**
     * @brief Constructs a VelocityChart object.
     *
     * @param[in] parent - The parent widget of the chart view.
     */
    VelocityChart(QWidget *parent = nullptr);

    /**
     * @brief Destroys the VelocityChart object.
     */
    ~VelocityChart();

    /**
     * @brief Updates the chart with a new data point.
     *
     * This method calculates the velocity based on the new position and the
     * elapsed time, and updates the chart with the new velocity value.
     *
     * @param[in] newPosition - The new position point.
     * @param[in] elapsedTime - The time elapsed since the last position update.
     */
    void update(const QPointF& newPosition, const int elapsedTime);

private slots:
    /**
     * @brief Slot to update the chart with random data.
     *
     * This slot appends a random value to the chart series and adjusts the
     * x-axis range if necessary.
     */
    void updateChart();


private:
    QLineSeries *m_series;  ///< The series of data points for the chart.
    QPointF lastPosition;   ///< The last position point used to calculate velocity.
    int m_x;                ///< The current x-value for the chart series.
};

#endif // CHARTS_H
