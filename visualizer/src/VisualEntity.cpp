#include "VisualEntity.h"
#include <QPainter>
#include <QGraphicsScene>

QRectF VisualEntity::boundingRect() const {
    return QRectF(0,0,100,100); //relative coordinate system for bounding rect
}

void VisualEntity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::blue);
    this->setZValue(Z_VALUE_PRIORITY);
    painter->drawText(10,25,QString::fromStdString(DEFAULT_TEXT));
}