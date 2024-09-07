#include "PrimaryBow.h"

PrimaryBow::PrimaryBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenPrimaryBow::WoodenPrimaryBow(QGraphicsItem *parent) :
    PrimaryBow(parent, ":/Items/RangedWeapons/Bow/primary_bow_wooden.png")
{
}

MetalPrimaryBow::MetalPrimaryBow(QGraphicsItem *parent) :
    PrimaryBow(parent, ":/Items/RangedWeapons/Bow/primary_bow_metal.png")
{
    initStateObjs();
}

MetalPrimaryBow::~MetalPrimaryBow()
{
    clearStateMap();
    uninitStateObjs();
}

bool MetalPrimaryBow::isShock()
{
    return CMetal::isShock();
}

void MetalPrimaryBow::beHit(QString element)
{
    CMetal::beHit(element);
}

void MetalPrimaryBow::beTrans(QString element, Item* srcItem)
{
    CMetal::beTrans(element);
}

void MetalPrimaryBow::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/RangedWeapons/Bow/bow_shock.png"));
        m_shockingPicture->setParentItem(pixmapItem);
        m_shockingPicture->setPos(0, 0);
    }
}
