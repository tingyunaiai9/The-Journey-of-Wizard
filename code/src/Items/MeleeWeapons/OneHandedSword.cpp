#include "OneHandedSword.h"

OneHandedSword::OneHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    MeleeWeapon(parent, pixmapPath)
{
}

void OneHandedSword::equipToParent() {
    MeleeWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

WoodenOneHandedSword::WoodenOneHandedSword(QGraphicsItem *parent) :
    OneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_wooden.png")
{
}

MetalOneHandedSword::MetalOneHandedSword(QGraphicsItem *parent) :
    OneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_metal.png")
{
}