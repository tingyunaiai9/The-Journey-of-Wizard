#include "MetalPlatform.h"

MetalPlatform::MetalPlatform(QGraphicsItem *parent) :
    Platform(parent, ":/Items/Maps/MetalPlatform/platform_metal.png")
{
    setPos(650, 300);

    m_metalNormal = new CMetalNormal(this);
    m_metalShocking = new CMetalShocking(this);

    addState(ENORMAL, m_metalNormal);
    addState(SHOCKING, m_metalShocking);

    initState(ENORMAL);
}

MetalPlatform::~MetalPlatform()
{
    clearStateMap();

    if (m_metalNormal)
    {
        delete(m_metalNormal);
    }

    if (m_metalShocking)
    {
        delete(m_metalShocking);
    }
}

void MetalPlatform::beHit(QString element)
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void MetalPlatform::onTimeOut()
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->timeOut();
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

void MetalPlatform::e_stopShocking()
{
    if (m_shockingPicture)
    {
        delete m_shockingPicture;
        m_shockingPicture = nullptr;
    }
}
