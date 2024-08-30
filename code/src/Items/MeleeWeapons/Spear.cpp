#include "Spear.h"

Spear::Spear(QGraphicsItem *parent, const QString &pixmapPath) :
    MeleeWeapon(parent, pixmapPath)
{
}

void Spear::equipToParent() {
    MeleeWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Spear::unequip() {
    MeleeWeapon::unequip();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 15);
    }
}

void Spear::startAttack() {
    MeleeWeapon::startAttack();

    //rotate
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(45);
        pixmapItem->setPos(25, -5);
    }
}

void Spear::stopAttack() {
    MeleeWeapon::stopAttack();

    //rotate back
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(0);
        pixmapItem->setPos(0, 0);
    }
}

WoodenSpear::WoodenSpear(QGraphicsItem *parent) :
    Spear(parent, ":/Items/MeleeWeapons/Spear/spear_wooden.png")
{
}

FlameSpear::FlameSpear(QGraphicsItem *parent) :
    Spear(parent, ":/Items/MeleeWeapons/Spear/spear_flame.png")
{
}

IceSpear::IceSpear(QGraphicsItem *parent) :
    Spear(parent, ":/Items/MeleeWeapons/Spear/spear_ice.png")
{
}

ElectroSpear::ElectroSpear(QGraphicsItem *parent) :
    Spear(parent, ":/Items/MeleeWeapons/Spear/spear_electro.png")
{
}
