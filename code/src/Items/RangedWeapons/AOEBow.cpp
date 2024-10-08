#include "AOEBow.h"

AOEBow::AOEBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenAOEBow::WoodenAOEBow(QGraphicsItem *parent) :
    AOEBow(parent, ":/Items/RangedWeapons/Bow/AOE_bow_wooden.png")
{
    initStateObjs();
}

WoodenAOEBow::~WoodenAOEBow()
{
    clearStateMap();
    uninitStateObjs();
}

bool WoodenAOEBow::isBurn()
{
    return CWood::isBurn();
}

bool WoodenAOEBow::isOut()
{
    return CWood::isOut();
}

void WoodenAOEBow::beHit(QString element)
{
    CWood::beHit(element);
}

void WoodenAOEBow::beTrans(QString element, Item* srcItem)
{
    CWood::beTrans(element);
}

void WoodenAOEBow::e_startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/RangedWeapons/Bow/bow_burning.png"));
        m_burningPicture->setParentItem(pixmapItem);
        m_burningPicture->setPos(0, 0);
    }
}

MetalAOEBow::MetalAOEBow(QGraphicsItem *parent) :
    AOEBow(parent, ":/Items/RangedWeapons/Bow/AOE_bow_metal.png")
{
    initStateObjs();
}

MetalAOEBow::~MetalAOEBow()
{
    clearStateMap();
    uninitStateObjs();
}

bool MetalAOEBow::isShock()
{
    return CMetal::isShock();
}

void MetalAOEBow::beHit(QString element)
{
    CMetal::beHit(element);
}

void MetalAOEBow::beTrans(QString element, Item* srcItem)
{
    CMetal::beTrans(element);
}

void MetalAOEBow::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/RangedWeapons/Bow/bow_shock.png"));
        m_shockingPicture->setParentItem(pixmapItem);
        m_shockingPicture->setPos(0, 0);
    }
}
