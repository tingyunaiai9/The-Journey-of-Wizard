#include "PrimaryBow.h"

PrimaryBow::PrimaryBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenPrimaryBow::WoodenPrimaryBow(QGraphicsItem *parent) :
    PrimaryBow(parent, ":/Items/RangedWeapons/Bow/primary_bow_wooden.png")
{
}

MetalPrimaryBow::MetalPrimaryBow(QGraphicsItem *parent) :
    PrimaryBow(parent, ":/Items/RangedWeapons/Bow/primary_bow_metal.png")
{
}
