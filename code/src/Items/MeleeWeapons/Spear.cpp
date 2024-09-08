#include "Spear.h"

Spear::Spear(QGraphicsItem *parent, const QString &pixmapPath) :
    MeleeWeapon(parent, pixmapPath)
{
}

void Spear::equipToParent()
{
    MeleeWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(0, 0);
    }
}

void Spear::unequip()
{
    MeleeWeapon::unequip();
    setScale(4);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(0, 15);
    }
}

void Spear::startAttack()
{
    MeleeWeapon::startAttack();

    //rotate
    if (pixmapItem != nullptr)
    {
        pixmapItem->setRotation(45);
        pixmapItem->setPos(25, -5);
    }
}

void Spear::stopAttack()
{
    MeleeWeapon::stopAttack();

    //rotate back
    if (pixmapItem != nullptr)
    {
        pixmapItem->setRotation(0);
        pixmapItem->setPos(0, 0);
    }
}

WoodenSpear::WoodenSpear(QGraphicsItem *parent, const QString &pixmapPath) :
    Spear(parent, pixmapPath)
{
    initStateObjs();
}

WoodenSpear::~WoodenSpear()
{
    clearStateMap();
    uninitStateObjs();
}

bool WoodenSpear::isBurn()
{
    return CWood::isBurn();
}

bool WoodenSpear::isOut()
{
    return CWood::isOut();
}

void WoodenSpear::beHit(QString element)
{
    CWood::beHit(element);
}

void WoodenSpear::beTrans(QString element, Item* srcItem)
{
    CWood::beTrans(element);
}

void WoodenSpear::e_startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/MeleeWeapons/Spear/spear_burning.png"));
        m_burningPicture->setParentItem(pixmapItem);
        m_burningPicture->setPos(0, 0);
    }
}

MetalSpear::MetalSpear(QGraphicsItem *parent, const QString &pixmapPath) :
    Spear(parent, pixmapPath)
{
    initStateObjs();
}

MetalSpear::~MetalSpear()
{
    clearStateMap();
    uninitStateObjs();
}

bool MetalSpear::isShock()
{
    return CMetal::isShock();
}

void MetalSpear::beHit(QString element)
{
    CMetal::beHit(element);
}

void MetalSpear::beTrans(QString element, Item* srcItem)
{
    CMetal::beTrans(element);
}

void MetalSpear::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/MeleeWeapons/Spear/spear_shock.png"));
        m_shockingPicture->setParentItem(pixmapItem);
        m_shockingPicture->setPos(0, 0);
    }
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
