#include "OneHandedSword.h"

OneHandedSword::OneHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    MeleeWeapon(parent, pixmapPath)
{
}

void OneHandedSword::equipToParent()
{
    MeleeWeapon::equipToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(0, 0);
    }
}

void OneHandedSword::unequip()
{
    MeleeWeapon::unequip();
    setScale(4);
    if (pixmapItem != nullptr)
    {
        pixmapItem->setPos(0, 15);
    }
}

void OneHandedSword::startAttack()
{
    MeleeWeapon::startAttack();

    //rotate
    if (pixmapItem != nullptr)
    {
        pixmapItem->setRotation(45);
        pixmapItem->setPos(25, -5);
    }
}

void OneHandedSword::stopAttack()
{
    MeleeWeapon::stopAttack();

    //rotate back
    if (pixmapItem != nullptr)
    {
        pixmapItem->setRotation(0);
        pixmapItem->setPos(0, 0);
    }
}

WoodenOneHandedSword::WoodenOneHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    OneHandedSword(parent, pixmapPath)
{
    initStateObjs();
}

WoodenOneHandedSword::~WoodenOneHandedSword()
{
    clearStateMap();
    uninitStateObjs();
}

bool WoodenOneHandedSword::isBurn()
{
    return CWood::isBurn();
}

bool WoodenOneHandedSword::isOut()
{
    return CWood::isOut();
}

void WoodenOneHandedSword::beHit(QString element)
{
    CWood::beHit(element);
}

void WoodenOneHandedSword::beTrans(QString element, Item* srcItem)
{
    CWood::beTrans(element);
}

void WoodenOneHandedSword::e_startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_burning.png"));
        m_burningPicture->setParentItem(pixmapItem);
        m_burningPicture->setPos(0, 0);
    }
}

MetalOneHandedSword::MetalOneHandedSword(QGraphicsItem *parent, const QString &pixmapPath) :
    OneHandedSword(parent, pixmapPath)
{
    initStateObjs();
}

MetalOneHandedSword::~MetalOneHandedSword()
{
    clearStateMap();
    uninitStateObjs();
}

bool MetalOneHandedSword::isShock()
{
    return CMetal::isShock();
}

void MetalOneHandedSword::beHit(QString element)
{
    CMetal::beHit(element);
}

void MetalOneHandedSword::beTrans(QString element, Item* srcItem)
{
    CMetal::beTrans(element);
}

void MetalOneHandedSword::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_shock.png"));
        m_shockingPicture->setParentItem(pixmapItem);
        m_shockingPicture->setPos(0, 0);
    }
}

NormalWoodenOneHandedSword::NormalWoodenOneHandedSword(QGraphicsItem *parent) :
    WoodenOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_wooden_normal.png")
{
}

FlameWoodenOneHandedSword::FlameWoodenOneHandedSword(QGraphicsItem *parent) :
    WoodenOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_wooden_flame.png")
{
}

IceWoodenOneHandedSword::IceWoodenOneHandedSword(QGraphicsItem *parent) :
    WoodenOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_wooden_ice.png")
{
}

ElectroWoodenOneHandedSword::ElectroWoodenOneHandedSword(QGraphicsItem *parent) :
    WoodenOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_wooden_electro.png")
{
}

NormalMetalOneHandedSword::NormalMetalOneHandedSword(QGraphicsItem *parent) :
    MetalOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_metal_normal.png")
{
}

FlameMetalOneHandedSword::FlameMetalOneHandedSword(QGraphicsItem *parent) :
    MetalOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_metal_flame.png")
{
}

IceMetalOneHandedSword::IceMetalOneHandedSword(QGraphicsItem *parent) :
    MetalOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_metal_ice.png")
{
}

ElectroMetalOneHandedSword::ElectroMetalOneHandedSword(QGraphicsItem *parent) :
    MetalOneHandedSword(parent, ":/Items/MeleeWeapons/OneHandedSword/one_handed_sword_metal_electro.png")
{
}
