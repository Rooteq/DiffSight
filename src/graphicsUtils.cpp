#include "graphicsUtils.h"

LineItem::LineItem(const QPointF& startPos, const QPointF& endPos, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_startPos(startPos), m_endPos(endPos) {}

QRectF LineItem::boundingRect() const {
    qreal penWidth = 10;
    return QRectF(m_startPos, m_endPos)
        .normalized()
        .adjusted(-penWidth / 2, -penWidth / 2, penWidth / 2, penWidth / 2);
}

void LineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen blackPen(Qt::black);
    blackPen.setWidth(2);

    painter->setPen(blackPen);
    painter->drawLine(m_startPos, m_endPos);
}

CrossItem::CrossItem(const QPointF& position, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_position(position) {
    setPos(m_position);
}

QRectF CrossItem::boundingRect() const {
    // Define the bounding box of the cross
    qreal size = 80; // Size of the cross arms
    return QRectF(-size / 2, -size / 2, size, size);
}

void CrossItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal size = 80; // Size of the cross arms
    painter->setPen(QPen(Qt::black, 2));
    painter->drawLine(-size / 2, 0, size / 2, 0); // Horizontal line
    painter->drawLine(0, -size / 2, 0, size / 2); // Vertical line
}

DotObject::DotObject(const QPointF& position, QGraphicsItem* parent)
    : QGraphicsItem(parent), m_position(position) {
    setPos(m_position);
    coloredBrush = Qt::blue;
}

QRectF DotObject::boundingRect() const {
    // Define the bounding box of the dot
    qreal radius = 5; // Radius of the dot
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

void DotObject::setColor(const QColor& color)
{
    coloredBrush.setColor(color);
}


void DotObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal radius = 5; // Radius of the dot

    painter->setBrush(coloredBrush);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(QPointF(0, 0), radius, radius);
}
