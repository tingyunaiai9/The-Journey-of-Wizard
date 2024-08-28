#include "IHero.h"

IState::IState(IHero* heroObj)
{
    m_HeroObj = heroObj;
}

QString IState::GetName()
{
    return "IState";
}

IState* IHero::GetStateObj()
{
    return m_StateMap[m_State];
}

void IHero::InitState(HEROSTATE stateType)
{
    m_State = stateType;
}

void IHero::SetState(HEROSTATE stateType)
{
    m_State = stateType;
}

void IHero::AddState(HEROSTATE stateType, IState* stateObj)
{
    m_StateMap[stateType] = stateObj;
}

void IHero::ClearStateMap()
{
    m_StateMap.clear();
}
