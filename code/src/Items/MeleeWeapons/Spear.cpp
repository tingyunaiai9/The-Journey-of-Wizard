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

WoodenSpear::WoodenSpear(QGraphicsItem *parent, const QString &pixmapPath) :
    Spear(parent, pixmapPath)
{
}

MetalSpear::MetalSpear(QGraphicsItem *parent, const QString &pixmapPath) :
    Spear(parent, pixmapPath)
{
}

NormalWoodenSpear::NormalWoodenSpear(QGraphicsItem *parent) :
    WoodenSpear(parent, ":/Items/MeleeWeapons/Spear/spear_wooden_normal.png")
{
}

FlameWoodenSpear::FlameWoodenSpear(QGraphicsItem *parent) :
    WoodenSpear(parent, ":/Items/MeleeWeapons/Spear/spear_wooden_flame.png")
{
}

IceWoodenSpear::IceWoodenSpear(QGraphicsItem *parent) :
    WoodenSpear(parent, ":/Items/MeleeWeapons/Spear/spear_wooden_ice.png")
{
}

ElectroWoodenSpear::ElectroWoodenSpear(QGraphicsItem *parent) :
    WoodenSpear(parent, ":/Items/MeleeWeapons/Spear/spear_wooden_electro.png")
{
}

NormalMetalSpear::NormalMetalSpear(QGraphicsItem *parent) :
    MetalSpear(parent, ":/Items/MeleeWeapons/Spear/spear_metal_normal.png")
{
}

FlameMetalSpear::FlameMetalSpear(QGraphicsItem *parent) :
    MetalSpear(parent, ":/Items/MeleeWeapons/Spear/spear_metal_flame.png")
{
}

IceMetalSpear::IceMetalSpear(QGraphicsItem *parent) :
    MetalSpear(parent, ":/Items/MeleeWeapons/Spear/spear_metal_ice.png")
{
}

ElectroMetalSpear::ElectroMetalSpear(QGraphicsItem *parent) :
    MetalSpear(parent, ":/Items/MeleeWeapons/Spear/spear_metal_electro.png")
{
}
