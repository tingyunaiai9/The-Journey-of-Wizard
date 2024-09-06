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
    uninitStateObjs();
}

void MetalPrimaryBow::beHit(QString element)
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void MetalPrimaryBow::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/MetalPlatform/platform_shock.png"));
        m_shockingPicture->setParentItem(this);
        m_shockingPicture->setRotation(-90);
        m_shockingPicture->setPos(32, 16);
    }
}
