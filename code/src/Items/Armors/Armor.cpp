#include "Armor.h"

Armor::Armor(QGraphicsItem *parent, const QString &pixmapPath) :
    Mountable(parent, pixmapPath)
{
}

void Armor::mountToParent() {
    Mountable::mountToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Armor::unmount() {
    Mountable::unmount();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 5);
    }
}

QPointF Armor::getCenterPos()
{
    QPointF centerPos = pos();
    centerPos.setX(centerPos.x() + 48);
    return centerPos;
}
