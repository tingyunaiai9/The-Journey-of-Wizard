#include "Item.h"

#include <QDebug>

const QPointF Item::GRAVITY = (QPointF(0, 0.004));

Item::Item(QGraphicsItem *parent, const QString &pixmapPath) :
    QGraphicsItem(parent)
{
    if (pixmapPath != "") {
        pixmapItem = new QGraphicsPixmapItem(QPixmap(pixmapPath), this);
    }
}
