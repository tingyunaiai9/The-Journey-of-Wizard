#include "WoodPlatform.h"


#include "./Map.h"

WoodPlatform::WoodPlatform(QGraphicsItem *parent) :
    Platform(parent, ":/Items/Maps/WoodPlatform/platform_wood.png")
{
    setPos(360, 440);

    m_woodNormal = new CWoodNormal(this);
    m_woodBurning = new CWoodBurning(this);

    addState(NORMAL, m_woodNormal);
    addState(BURNING, m_woodBurning);

    initState(NORMAL);
}

WoodPlatform::~WoodPlatform()
{
    clearStateMap();

    if (m_woodNormal)
    {
        delete(m_woodNormal);
    }

    if (m_woodBurned)
    {
        delete(m_woodBurned);
    }

    if (m_woodBurning)
    {
        delete(m_woodBurning);
    }

    if (m_woodBurnout)
    {
        delete(m_woodBurnout);
    }
}

void WoodPlatform::beHit(QString element)
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void WoodPlatform::onTimeOut()
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->timeOut();
}

void WoodPlatform::e_startBurning()
{
    if (m_burningPicture == nullptr)
    {
        m_burningPicture = new QGraphicsPixmapItem(QPixmap(":/Items/Characters/character_burning.png"));
        m_burningPicture->setParentItem(this);
        m_burningPicture->setPos(0, -32);
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
