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

void OneHandedSword::unequip() {
    MeleeWeapon::unequip();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 15);
    }
}

void OneHandedSword::startAttack() {
    MeleeWeapon::startAttack();

    //rotate
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(45);
        pixmapItem->setPos(25, -5);
    }
}

void OneHandedSword::stopAttack() {
    MeleeWeapon::stopAttack();

    //rotate back
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(0);
        pixmapItem->setPos(0, 0);
    }
}

WoodenOneHandedSword::WoodenOneHandedSword(QGraphicsItem *parent) :
    OneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_wooden.png")
{
}

FlameOneHandedSword::FlameOneHandedSword(QGraphicsItem *parent) :
    OneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_flame.png")
{
}

IceOneHandedSword::IceOneHandedSword(QGraphicsItem *parent) :
    OneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_ice.png")
{
}

ElectroOneHandedSword::ElectroOneHandedSword(QGraphicsItem *parent) :
    OneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_electro.png")
{
}
