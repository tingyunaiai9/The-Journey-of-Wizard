#include "IMetal.h"

#include <QDebug>

IShockState::IShockState(IMetal* metalObj)
{
    m_metalObj = metalObj;
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
