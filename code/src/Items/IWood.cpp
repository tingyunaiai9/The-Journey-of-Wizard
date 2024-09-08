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

// IWood
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
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();
    QString name_1 = state_obj->getName();

    m_State = stateType;

    state_obj = getStateObj();
    QString name_2 = state_obj->getName();

    // qDebug() << name_1 << " --> " << name_2;
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

void CWoodNormal::beTrans(QString element)
{
    if (element == "Flame")
    {
        m_woodObj->setState(BURNED);
        m_timeout->start(2000);
    }
}

CWoodBurned::CWoodBurned(IWood* woodObj):
    IBurnState(woodObj)
{
}

void CWoodBurned::timeOut()
{
    m_woodObj->e_startBurning();
    m_woodObj->setState(BURNING);
    m_timeout->start(10000);
}

CWoodBurning::CWoodBurning(IWood* woodObj):
    IBurnState(woodObj)
{
}

void CWoodBurning::timeOut()
{
    m_woodObj->e_stopBurning();
    m_woodObj->setState(BURNOUT);
}

CWoodBurnout::CWoodBurnout(IWood* woodObj):
    IBurnState(woodObj)
{
}

void CWood::initStateObjs()
{
    m_woodNormal = new CWoodNormal(this);
    m_woodBurned = new CWoodBurned(this);
    m_woodBurning = new CWoodBurning(this);
    m_woodBurnout = new CWoodBurnout(this);

    addState(FNORMAL, m_woodNormal);
    addState(BURNED, m_woodBurned);
    addState(BURNING, m_woodBurning);
    addState(BURNOUT, m_woodBurnout);

    initState(FNORMAL);
}

void CWood::uninitStateObjs()
{
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

bool CWood::isBurn()
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    return state_obj->isBurn();
}

bool CWood::isOut()
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    return state_obj->isOut();
}

void CWood::beHit(QString element)
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(element);
}

void CWood::beTrans(QString element)
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beTrans(element);
}

void CWood::onTimeOut()
{
    IBurnState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->timeOut();
}

void CWood::e_stopBurning()
{
    if (m_burningPicture)
    {
        delete m_burningPicture;
        m_burningPicture = nullptr;
    }
}
