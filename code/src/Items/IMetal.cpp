#include "IMetal.h"

#include <QDebug>

IShockState::IShockState(IMetal* metalObj)
{
    m_metalObj = metalObj;
    m_timeout = new QTimer(this);
    m_timeout->setSingleShot(true);  // only once
    connect(m_timeout, &QTimer::timeout, metalObj, &IMetal::onTimeOut);
}

IShockState::~IShockState()
{
    if (m_timeout)
    {
        delete(m_timeout);
    }
}

//
IShockState* IMetal::getStateObj()
{
    return m_StateMap[m_State];
}

void IMetal::initState(METALSTATE stateType)
{
    m_State = stateType;
}

void IMetal::setState(METALSTATE stateType)
{
    IShockState* state_obj = NULL;
    state_obj = getStateObj();
    QString name_1 = state_obj->getName();

    m_State = stateType;

    state_obj = getStateObj();
    QString name_2 = state_obj->getName();

    qDebug() << name_1 << " --> " << name_2;
}

void IMetal::addState(METALSTATE stateType, IShockState* stateObj)
{
    m_StateMap[stateType] = stateObj;
}

void IMetal::clearStateMap()
{
    m_StateMap.clear();
}

CMetalNormal::CMetalNormal(IMetal* metalObj):
    IShockState(metalObj)
{
}

void CMetalNormal::beHit(QString element)
{
    if (element == "Electro")
    {
        m_metalObj->e_startShocking();
        m_metalObj->setState(SHOCKING);
        m_timeout->start(2000);
    }
}

CMetalShocking::CMetalShocking(IMetal* MetalObj):
    IShockState(MetalObj)
{
}

void CMetalShocking::timeOut()
{
    m_metalObj->e_stopShocking();
    m_metalObj->setState(ENORMAL);
}

void CMetal::initStateObjs()
{
    m_metalNormal = new CMetalNormal(this);
    m_metalShocking = new CMetalShocking(this);

    addState(ENORMAL, m_metalNormal);
    addState(SHOCKING, m_metalShocking);

    initState(ENORMAL);
}

void CMetal::uninitStateObjs()
{
    if (m_metalNormal)
    {
        delete(m_metalNormal);
    }

    if (m_metalShocking)
    {
        delete(m_metalShocking);
    }
}

void CMetal::onTimeOut()
{
    IShockState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->timeOut();
}

void CMetal::e_stopShocking()
{
    if (m_shockingPicture)
    {
        delete m_shockingPicture;
        m_shockingPicture = nullptr;
    }
}
