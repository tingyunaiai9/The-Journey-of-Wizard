#include "WoodPlatform.h"

WoodPlatform::WoodPlatform(QGraphicsItem *parent) :
    Platform(parent, ":/Items/Maps/WoodPlatform/platform_wood.png")
{
    setPos(360, 440);
    initStateObjs();
}

WoodPlatform::~WoodPlatform()
{
    clearStateMap();
    uninitStateObjs();
}

bool WoodPlatform::isBurn()
{
    return CWood::isBurn();
}

bool WoodPlatform::isOut()
{
    return CWood::isOut();
}

void WoodPlatform::beHit(QString element)
{
    CWood::beHit(element);
}

void WoodPlatform::beTrans(QString element, Item* srcItem)
{
    CWood::beTrans(element);
}

void WoodPlatform::e_startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Maps/WoodPlatform/platform_burning.png"));
        m_burningPicture->setParentItem(this);
        m_burningPicture->setPos(0, -14);
    }
}
