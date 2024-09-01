#include "Arrow.h"

Arrow::Arrow(QGraphicsItem *parent, const QString &pixmapPath) :
    RangedWeapon(parent, pixmapPath)
{
}

void Arrow::equipToParent()
{
    RangedWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Arrow::unequip()
{
    RangedWeapon::unequip();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(-23, 33);
    }
}

NormalArrow::NormalArrow(QGraphicsItem *parent) :
    Arrow(parent, ":/Items/RangedWeapons/Arrow/arrow_normal.png")
{
}

FlameArrow::FlameArrow(QGraphicsItem *parent) :
    Arrow(parent, ":/Items/RangedWeapons/Arrow/arrow_flame.png")
{
}

IceArrow::IceArrow(QGraphicsItem *parent) :
    Arrow(parent, ":/Items/RangedWeapons/Arrow/arrow_ice.png")
{
}

ElectroArrow::ElectroArrow(QGraphicsItem *parent) :
    Arrow(parent, ":/Items/RangedWeapons/Arrow/arrow_electro.png")
{
}
