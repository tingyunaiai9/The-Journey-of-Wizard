#include "TwoHandedSword.h"

TwoHandedSword::TwoHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    MeleeWeapon(parent, pixmapPath)
{
}

void TwoHandedSword::equipToParent() {
    MeleeWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void TwoHandedSword::unequip() {
    MeleeWeapon::unequip();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 15);
    }
}

void TwoHandedSword::startAttack() {
    MeleeWeapon::startAttack();

    //rotate
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(45);
        pixmapItem->setPos(25, -5);
    }
}

void TwoHandedSword::stopAttack() {
    MeleeWeapon::stopAttack();

    //rotate back
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(0);
        pixmapItem->setPos(0, 0);
    }
}

WoodenTwoHandedSword::WoodenTwoHandedSword(QGraphicsItem *parent) :
    TwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_wooden.png")
{
}

FlameTwoHandedSword::FlameTwoHandedSword(QGraphicsItem *parent) :
    TwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_flame.png")
{
}

IceTwoHandedSword::IceTwoHandedSword(QGraphicsItem *parent) :
    TwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_ice.png")
{
}

ElectroTwoHandedSword::ElectroTwoHandedSword(QGraphicsItem *parent) :
    TwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_electro.png")
{
}
