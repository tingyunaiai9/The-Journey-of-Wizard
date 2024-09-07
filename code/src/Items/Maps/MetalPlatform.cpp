#include "MetalPlatform.h"

MetalPlatform::MetalPlatform(QGraphicsItem *parent) :
    Platform(parent, ":/Items/Maps/MetalPlatform/platform_metal.png")
{
    setPos(650, 300);

    initStateObjs();
}

MetalPlatform::~MetalPlatform()
{
    clearStateMap();
    uninitStateObjs();
}

bool MetalPlatform::isShock()
{
    return CMetal::isShock();
}

void MetalPlatform::beHit(QString element)
{
    CMetal::beHit(element);
}

void MetalPlatform::beTrans(QString element, Item* srcItem)
{
    CMetal::beTrans(element);
}

void MetalPlatform::e_startShocking()
{
    if (m_shockingPicture == nullptr)
    {
        m_shockingPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/MetalPlatform/platform_shock.png"));
        m_shockingPicture->setParentItem(this);
        m_shockingPicture->setPos(0, 0);
    }
}
