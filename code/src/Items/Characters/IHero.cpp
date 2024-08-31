#include "IHero.h"

IState::IState(IHero* heroObj)
{
    m_HeroObj = heroObj;
}

//
IState* IHero::getStateObj()
{
    return m_StateMap[m_State];
}

void IHero::initState(HEROSTATE stateType)
{
    m_State = stateType;
}

void IHero::setState(HEROSTATE stateType)
{
    m_State = stateType;
}

void IHero::addState(HEROSTATE stateType, IState* stateObj)
{
    m_StateMap[stateType] = stateObj;
}

void IHero::clearStateMap()
{
    m_StateMap.clear();
}

// IHode, IAttacking, IHitting
IHold::IHold(IHero* heroObj):
    IState(heroObj)
{
}

void IHold::setAttack()
{
    // TODO: check if the hero is holding a weapon
    m_HeroObj->h_startAttack();
}

void IHold::beHit(int damage, QString element)
{
    m_HeroObj->h_startHitting();
    m_HeroObj->h_reduceHp(damage);
    // TODO: override the function in the derived class to change element

    m_HeroObj->setState(HEROSTATE::NORMAL_HITTING); // TODO: need to delete
}

IAttacking::IAttacking(IHero* heroObj):
    IState(heroObj)
{
}

bool IAttacking::isAttacking()
{
    return true;
}

void IAttacking::processFps(qint64 deltaTime)
{
    m_elapsedTime += deltaTime;

    // TODO: 时间到了切换武器状态回
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->h_stopAttack();
    }
}

IHitting::IHitting(IHero* heroObj):
    IState(heroObj)
{
}

bool IHitting::isHitting()
{
    return true;
}

void IHitting::processFps(qint64 deltaTime)
{
    m_elapsedTime += deltaTime;

    // TODO: 时间到了切换打击状态回
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->h_stopHitting();
    }
}

// hold
CNormalHold::CNormalHold(IHero* heroObj):
    IHold(heroObj)
{
}

QString CNormalHold::getName()
{
    return "NormalHold";
}

// change the state to normal attacking
void CNormalHold::setAttack()
{
    IHold::setAttack();
    // TODO: set timer to quit attacking
    // or fps?

    // TODO: change the state of weapon to attacking



    m_HeroObj->setState(HEROSTATE::NORMAL_ATTACKING);
}

CFlameHold::CFlameHold(IHero* heroObj):
    IHold(heroObj)
{
}

QString CFlameHold::getName()
{
    return "FlameHold";
}

CIceHold::CIceHold(IHero* heroObj):
    IHold(heroObj)
{
}

QString CIceHold::getName()
{
    return "IceHold";
}

CElectroHold::CElectroHold(IHero* heroObj):
    IHold(heroObj)
{
}

QString CElectroHold::getName()
{
    return "ElectroHold";
}

// attacking
CNormalAttacking::CNormalAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

QString CNormalAttacking::getName()
{
    return "NormalAttacking";
}

void CNormalAttacking::processFps(qint64 deltaTime)
{
    IAttacking::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
        m_elapsedTime = 0;
    }
}

CFlameAttacking::CFlameAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

QString CFlameAttacking::getName()
{
    return "FlameAttacking";
}

void CFlameAttacking::processFps(qint64 deltaTime)
{
    IAttacking::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::FLAME_HOLD);
        m_elapsedTime = 0;
    }
}

CIceAttacking::CIceAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

QString CIceAttacking::getName()
{
    return "IceAttacking";
}

void CIceAttacking::processFps(qint64 deltaTime)
{
    IAttacking::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::ICE_HOLD);
        m_elapsedTime = 0;
    }
}

CElectroAttacking::CElectroAttacking(IHero* heroObj):
    IAttacking(heroObj)
{
}

QString CElectroAttacking::getName()
{
    return "ElectroAttacking";
}

void CElectroAttacking::processFps(qint64 deltaTime)
{
    IAttacking::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::ELECTRO_HOLD);
        m_elapsedTime = 0;
    }
}

// hitting
CNormalHitting::CNormalHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

QString CNormalHitting::getName()
{
    return "NormalHitting";
}

void CNormalHitting::processFps(qint64 deltaTime)
{
    IHitting::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
        m_elapsedTime = 0;
    }
}

CFlameHitting::CFlameHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

QString CFlameHitting::getName()
{
    return "FlameHitting";
}

void CFlameHitting::processFps(qint64 deltaTime)
{
    IHitting::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::FLAME_HOLD);
        m_elapsedTime = 0;
    }
}

CIceHitting::CIceHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

QString CIceHitting::getName()
{
    return "IceHitting";
}

void CIceHitting::processFps(qint64 deltaTime)
{
    IHitting::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::ICE_HOLD);
        m_elapsedTime = 0;
    }
}

CElectroHitting::CElectroHitting(IHero* heroObj):
    IHitting(heroObj)
{
}

QString CElectroHitting::getName()
{
    return "ElectroHitting";
}

void CElectroHitting::processFps(qint64 deltaTime)
{
    IHitting::processFps(deltaTime);
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->setState(HEROSTATE::ELECTRO_HOLD);
        m_elapsedTime = 0;
    }
}
