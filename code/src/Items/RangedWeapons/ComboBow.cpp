#include "ComboBow.h"

ComboBow::ComboBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenComboBow::WoodenComboBow(QGraphicsItem *parent) :
    ComboBow(parent, ":/Items/RangedWeapons/Bow/combo_bow_wooden.png")
{
}

MetalComboBow::MetalComboBow(QGraphicsItem *parent) :
    ComboBow(parent, ":/Items/RangedWeapons/Bow/combo_bow_metal.png")
{
    initStateObjs();
}

MetalComboBow::~MetalComboBow()
{
    uninitStateObjs();
}

void MetalComboBow::beHit(QString element)
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void MetalComboBow::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/MetalPlatform/platform_shock.png"));
        m_shockingPicture->setParentItem(this);
        m_shockingPicture->setRotation(-90);
        m_shockingPicture->setPos(32, 16);
    }
}
