#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath) :
    Weapon(parent, pixmapPath)
{
}

void MeleeWeapon::shoot(bool isFacingRight, QPointF velocity)
{
    Weapon::shoot(isFacingRight, velocity);

    pixmapItem->setRotation(45);
    setPos(pos().x(), pos().y() - 60); // above ground

    pixmapItem->setPos(25, 5); // drop into ground
}
