/**
 * @file graphicsUtils.h
 * @brief This file contains the declarations for graphical items used in the graphics view.
 * @version 0.1
 *
 * @details This file contains the classes LineItem, CrossItem, and DotObject, which are used
 * to draw graphical elements on a QGraphicsView.
 *
 */

#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include <QtWidgets>

/**
 * @brief Number of line segments
 */
constexpr unsigned int LINES_SEGMENTS = 50;
constexpr unsigned int NUM_DOTS = 500;

/**
 * @class LineItem
 * @brief Custom QGraphicsItem to represent a line.
 */
class LineItem : public QGraphicsItem
{
public:
    /**
     * @brief Constructor for LineItem.
     * @param[in] startPos The starting position of the line.
     * @param[in] endPos The ending position of the line.
     * @param[in] parent The parent QGraphicsItem, default is nullptr.
     */
    LineItem(const QPointF& startPos, const QPointF& endPos, QGraphicsItem* parent = nullptr);

    /**
     * @brief Defines the bounding rectangle for the item.
     * @return The bounding rectangle.
     */
    QRectF boundingRect() const override;

    /**
     * @brief Paints the line item.
     * @param[in] painter - The painter used to draw the item.
     * @param[in] option - Provides style options for the item.
     * @param[in] widget - The widget that is being painted on.
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPointF m_startPos; /**< The starting position of the line */
    QPointF m_endPos; /**< The ending position of the line */
};

/**
 * @class CrossItem
 * @brief Custom QGraphicsItem to represent a cross.
 */
class CrossItem : public QGraphicsItem {
public:
    /**
     * @brief Constructor for CrossItem.
     * @param[in] position - The center position of the cross.
     * @param[in] parent - The parent QGraphicsItem, default is nullptr.
     */
    CrossItem(const QPointF& position, QGraphicsItem* parent = nullptr);

    /**
     * @brief Defines the bounding rectangle for the item.
     * @return The bounding rectangle.
     */
    QRectF boundingRect() const override;

    /**
     * @brief Paints the cross item.
     * @param[in] painter - The painter used to draw the item.
     * @param[in] option - Provides style options for the item.
     * @param[in] widget - The widget that is being painted on.
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPointF m_position; /**< The center position of the cross */
};

/**
 * @class DotObject
 * @brief Custom QGraphicsItem to represent a dot.
 */
class DotObject : public QGraphicsItem {
public:
    /**
     * @brief Constructor for DotObject.
     * @param[in] position - The position of the dot.
     * @param[in] parent - The parent QGraphicsItem, default is nullptr.
     */
    DotObject(const QPointF& position, QGraphicsItem* parent = nullptr);

    /**
     * @brief Changes color of the dot.
     * @param[in] color - New color of the dot.
     */
    void setColor(const QColor& color);

    /**
     * @brief Defines the bounding rectangle for the item.
     * @return The bounding rectangle.
     */
    QRectF boundingRect() const override;

    /**
     * @brief Paints the dot item.
     * @param[in] painter - The painter used to draw the item.
     * @param[in] option - Provides style options for the item.
     * @param[in] widget - The widget that is being painted on.
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QBrush coloredBrush;
    QPointF m_position; ///< The position of the dot.
};

#endif // GRAPHICSUTILS_H
