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

void Bow::startAttack()
{
    RangedWeapon::startAttack();

    //rotate
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(45);
        pixmapItem->setPos(25, -5);
    }
}

void Bow::stopAttack()
{
    RangedWeapon::stopAttack();

    //rotate back
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(0);
        pixmapItem->setPos(0, 0);
    }
}
