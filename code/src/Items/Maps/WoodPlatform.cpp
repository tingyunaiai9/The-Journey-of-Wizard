#include "WoodPlatform.h"


#include "./Map.h"

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

void WoodPlatform::beHit(QString element)
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
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

void WoodPlatform::e_stopBurning()
{
    if (m_burningPicture)
    {
        delete m_burningPicture;
        m_burningPicture = nullptr;
    }

    emit burnOut(dynamic_cast<Map*>(this));
}
