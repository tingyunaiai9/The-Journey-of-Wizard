#include "Arrow.h"

Arrow::Arrow(QGraphicsItem *parent, const QString &pixmapPath) :
    RangedWeapon(parent, pixmapPath)
{
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
