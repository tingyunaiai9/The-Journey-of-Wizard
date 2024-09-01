#include "Bow.h"

Bow::Bow(QGraphicsItem *parent, const QString &pixmapPath) :
    RangedWeapon(parent, pixmapPath)
{
}

void Bow::equipToParent()
{
    RangedWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    setRotation(0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Bow::unequip()
{
    RangedWeapon::unequip();
    setScale(4);
    setRotation(80);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(20, -12);
    }
}
