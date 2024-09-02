#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath) :
    Weapon(parent, pixmapPath)
{
}

void MeleeWeapon::shoot(bool isFacingRight, QPointF velocity)
{
    Weapon::shoot(isFacingRight, velocity);

    pixmapItem->setRotation(45);
    if (isFacingRight)
    {
        setPos(pos().x() + 60, pos().y() - 60); // above ground
    }
    else
    {
        setPos(pos().x() - 60, pos().y() - 60);
    }

    pixmapItem->setPos(0, 5); // drop into ground
}

QRectF MeleeWeapon::getShootAttackRange()
{
    if (isFacingRight())
    {
        return QRectF(pos().x() - 55,
                      pos().y() - 24 + 60,
                      getAttackForwardDistance(),
                      48 + 50);
    }
    else
    {
        return QRectF(pos().x() - getAttackForwardDistance() + 55,
                      pos().y() - 24 + 60,
                      getAttackForwardDistance(),
                      48 + 50);
    }
}
