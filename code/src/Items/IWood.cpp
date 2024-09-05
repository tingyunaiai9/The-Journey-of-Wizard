#include "IWood.h"

#include <QDebug>

IBurnState::IBurnState(IWood* woodObj)
{
    m_woodObj = woodObj;
    m_timeout = new QTimer(this);
    m_timeout->setSingleShot(true);  // only once
    connect(m_timeout, &QTimer::timeout, woodObj, &IWood::onTimeOut);
}

IBurnState::~IBurnState()
{
    if (m_timeout)
    {
        delete(m_timeout);
    }
}

//
IBurnState* IWood::getStateObj()
{
    return m_StateMap[m_State];
}

void IWood::initState(WOODSTATE stateType)
{
    m_State = stateType;
}

void IWood::setState(WOODSTATE stateType)
{
    IBurnState* state_obj = NULL;
    state_obj = getStateObj();
    QString name_1 = state_obj->getName();

    m_State = stateType;

    state_obj = getStateObj();
    QString name_2 = state_obj->getName();

    qDebug() << name_1 << " --> " << name_2;
}

void IWood::addState(WOODSTATE stateType, IBurnState* stateObj)
{
    m_StateMap[stateType] = stateObj;
}

void IWood::clearStateMap()
{
    m_StateMap.clear();
}

CWoodNormal::CWoodNormal(IWood* woodObj):
    IBurnState(woodObj)
{
}

void CWoodNormal::beHit(QString element)
{
    if (element == "Flame")
    {
        m_woodObj->e_startBurning();
        m_woodObj->setState(BURNING);
        m_timeout->start(10000);
    }
}

CWoodBurned::CWoodBurned(IWood* woodObj):
    IBurnState(woodObj)
{
}

CWoodBurning::CWoodBurning(IWood* woodObj):
    IBurnState(woodObj)
{
}

void CWoodBurning::timeOut()
{
    m_woodObj->e_stopBurning();
}

CWoodBurnout::CWoodBurnout(IWood* woodObj):
    IBurnState(woodObj)
{
}
