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

WoodenTwoHandedSword::WoodenTwoHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    TwoHandedSword(parent, pixmapPath)
{
}

MetalTwoHandedSword::MetalTwoHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    TwoHandedSword(parent, pixmapPath)
{
    initStateObjs();
}

MetalTwoHandedSword::~MetalTwoHandedSword()
{
    uninitStateObjs();
}

void MetalTwoHandedSword::beHit(QString element)
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void MetalTwoHandedSword::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/MetalPlatform/platform_shock.png"));
        m_shockingPicture->setParentItem(this);
        m_shockingPicture->setPos(0, 32);
    }
}

NormalWoodenTwoHandedSword::NormalWoodenTwoHandedSword(QGraphicsItem *parent) :
    WoodenTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_wooden_normal.png")
{
}

FlameWoodenTwoHandedSword::FlameWoodenTwoHandedSword(QGraphicsItem *parent) :
    WoodenTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_wooden_flame.png")
{
}

IceWoodenTwoHandedSword::IceWoodenTwoHandedSword(QGraphicsItem *parent) :
    WoodenTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_wooden_ice.png")
{
}

ElectroWoodenTwoHandedSword::ElectroWoodenTwoHandedSword(QGraphicsItem *parent) :
    WoodenTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_wooden_electro.png")
{
}

NormalMetalTwoHandedSword::NormalMetalTwoHandedSword(QGraphicsItem *parent) :
    MetalTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_metal_normal.png")
{
}

FlameMetalTwoHandedSword::FlameMetalTwoHandedSword(QGraphicsItem *parent) :
    MetalTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_metal_flame.png")
{
}

IceMetalTwoHandedSword::IceMetalTwoHandedSword(QGraphicsItem *parent) :
    MetalTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_metal_ice.png")
{
}

ElectroMetalTwoHandedSword::ElectroMetalTwoHandedSword(QGraphicsItem *parent) :
    MetalTwoHandedSword(parent, ":/Items/MeleeWeapons/TwoHandedSword/two_handed_sword_metal_electro.png")
{
}
