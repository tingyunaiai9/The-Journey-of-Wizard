#include "ComboBow.h"

ComboBow::ComboBow(QGraphicsItem *parent, const QString &pixmapPath) :
    Bow(parent, pixmapPath)
{
}

WoodenComboBow::WoodenComboBow(QGraphicsItem *parent) :
    ComboBow(parent, ":/Items/RangedWeapons/Bow/combo_bow_wooden.png")
{
    initStateObjs();
}

WoodenComboBow::~WoodenComboBow()
{
    clearStateMap();
    uninitStateObjs();
}

bool WoodenComboBow::isBurn()
{
    return CWood::isBurn();
}

bool WoodenComboBow::isOut()
{
    return CWood::isOut();
}

void WoodenComboBow::beHit(QString element)
{
    CWood::beHit(element);
}

void WoodenComboBow::beTrans(QString element, Item* srcItem)
{
    CWood::beTrans(element);
}

void WoodenComboBow::e_startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/RangedWeapons/Bow/bow_burning.png"));
        m_burningPicture->setParentItem(pixmapItem);
        m_burningPicture->setPos(0, 0);
    }
}

MetalComboBow::MetalComboBow(QGraphicsItem *parent) :
    ComboBow(parent, ":/Items/RangedWeapons/Bow/combo_bow_metal.png")
{
    initStateObjs();
}

MetalComboBow::~MetalComboBow()
{
    clearStateMap();
    uninitStateObjs();
}

bool MetalComboBow::isShock()
{
    return CMetal::isShock();
}

void MetalComboBow::beHit(QString element)
{
    CMetal::beHit(element);
}

void MetalComboBow::beTrans(QString element, Item* srcItem)
{
    CMetal::beTrans(element);
}

void MetalComboBow::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/RangedWeapons/Bow/bow_shock.png"));
        m_shockingPicture->setParentItem(pixmapItem);
        m_shockingPicture->setPos(0, 0);
    }
}
