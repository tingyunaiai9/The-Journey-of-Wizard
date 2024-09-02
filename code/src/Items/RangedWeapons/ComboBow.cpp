#include "ComboBow.h"

ComboBow::ComboBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenComboBow::WoodenComboBow(QGraphicsItem *parent) :
    ComboBow(parent, ":/Items/RangedWeapons/Bow/combo_bow_wooden.png")
{
}

MetalComboBow::MetalComboBow(QGraphicsItem *parent) :
    ComboBow(parent, ":/Items/RangedWeapons/Bow/combo_bow_metal.png")
{
}
