#include "IHero.h"

IState::IState(IHero* heroObj)
{
    m_HeroObj = heroObj;
}

QString IState::GetName()
{
    return "IState";
}

bool IState::isAttacking()
{
    return false;
}

bool IState::isHitting()
{
    return false;
}

void IState::setAttack()
{
}

void IState::beHit(int damage, QString element)
{
}

//
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

//
IHold::IHold(IHero* heroObj):
    IState(heroObj)
{
}

IAttacking::IAttacking(IHero* heroObj):
    IState(heroObj)
{
}

bool IAttacking::isAttacking()
{
    return true;
}

IHitting::IHitting(IHero* heroObj):
    IState(heroObj)
{
}

bool IHitting::isHitting()
{
    return true;
}

//
CNormalHold::CNormalHold(IHero* heroObj):
    IHold(heroObj)
{
}

void CNormalHold::setAttack()
{
    // TODO: set timer to quit attacking



    m_HeroObj->SetState(HEROSTATE::NORMAL_ATTACKING);
}

CFlameHold::CFlameHold(IHero* heroObj):
    IHold(heroObj)
{
}

CIceHold::CIceHold(IHero* heroObj):
    IHold(heroObj)
{
}

CElectroHold::CElectroHold(IHero* heroObj):
    IHold(heroObj)
{
}

//
CNormalAttacking::CNormalAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

CFlameAttacking::CFlameAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

CIceAttacking::CIceAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

CElectroAttacking::CElectroAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

//
CNormalHitting::CNormalHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

CFlameHitting::CFlameHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

CIceHitting::CIceHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

CElectroHitting::CElectroHitting(IHero* heroObj):
    IHitting(heroObj)
{
}
