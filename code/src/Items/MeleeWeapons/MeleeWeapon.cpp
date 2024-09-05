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

QPointF MeleeWeapon::getCenterPos()
{
    QPointF centerPos = pos();
    centerPos.setX(centerPos.x() + 96);
    return centerPos;
}

QRectF MeleeWeapon::getAreaRect()
{
    QRectF itemRect = sceneBoundingRect();
    qreal x = itemRect.x();
    qreal y = itemRect.y();
    qreal cx = itemRect.width();
    qreal cy = itemRect.height();

    // itemRect.setX(x + 32);
    // itemRect.setWidth(cx - 32);

    itemRect.setY(y + 40);
    itemRect.setHeight(cy - 40 * 2);

    return itemRect;
}
