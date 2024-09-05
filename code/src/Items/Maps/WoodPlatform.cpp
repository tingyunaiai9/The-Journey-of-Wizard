#include "WoodPlatform.h"


#include "./Map.h"

WoodPlatform::WoodPlatform(QGraphicsItem *parent) :
    Platform(parent, ":/Items/Maps/WoodPlatform/platform_wood.png")
{
    setPos(360, 440);

    m_woodNormal = new CWoodNormal(this);
    m_woodBurned = new CWoodBurned(this);
    m_woodBurning = new CWoodBurning(this);

    addState(FNORMAL, m_woodNormal);
    addState(BURNED, m_woodBurned);
    addState(BURNING, m_woodBurning);

    initState(FNORMAL);
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
