#include "AOEBow.h"

AOEBow::AOEBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenAOEBow::WoodenAOEBow(QGraphicsItem *parent) :
    AOEBow(parent, ":/Items/RangedWeapons/Bow/AOE_bow_wooden.png")
{
}

MetalAOEBow::MetalAOEBow(QGraphicsItem *parent) :
    AOEBow(parent, ":/Items/RangedWeapons/Bow/AOE_bow_metal.png")
{
    initStateObjs();
}

MetalAOEBow::~MetalAOEBow()
{
    uninitStateObjs();
}

void MetalAOEBow::beHit(QString element)
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void MetalAOEBow::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/RangedWeapons/Bow/bow_shock.png"));
        m_shockingPicture->setParentItem(this);
        m_shockingPicture->setPos(20, -12);
    }
}
