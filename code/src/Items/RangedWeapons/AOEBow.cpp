#include "AOEBow.h"

AOEBow::AOEBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenAOEBow::WoodenAOEBow(QGraphicsItem *parent) :
    AOEBow(parent, ":/Items/RangedWeapons/Bow/AOE_bow_wooden.png")
{
}

MetalAOEBow::MetalAOEBow(QGraphicsItem *parent) :
    AOEBow(parent, ":/Items/RangedWeapons/Bow/AOE_bow_metal.png")
{
}
