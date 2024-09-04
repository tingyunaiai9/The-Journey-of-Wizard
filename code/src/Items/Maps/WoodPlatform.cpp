#include "WoodPlatform.h"

WoodPlatform::WoodPlatform(QGraphicsItem *parent) :
    Platform(parent, ":/Items/Maps/WoodPlatform/platform_wood.png")
{
    setPos(360, 440);
}

void WoodPlatform::startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Characters/character_burning.png"));
        m_burningPicture->setParentItem(this);
        m_burningPicture->setPos(0, -32);
    }
}

void WoodPlatform::stopBurning()
{
    if (m_burningPicture)
    {
        delete m_burningPicture;
        m_burningPicture = nullptr;
    }
}
