#include "IHero.h"

#include <QDebug>

IState::IState(IHero* heroObj)
{
    m_HeroObj = heroObj;
}

//
IState* IHero::getStateObj()
{
    return m_StateMap[m_State];
}

void IState::key_press(QKeyEvent *event)
{
    return m_HeroObj->h_keyPress(event);
}

void IState::key_release(QKeyEvent *event)
{
    return m_HeroObj->h_keyRelease(event);
}

void IHero::initState(HEROSTATE stateType)
{
    m_State = stateType;
}

void IHero::setState(HEROSTATE stateType)
{
    IState* state_obj = NULL;
    state_obj = getStateObj();
    QString name_1 = state_obj->getName();

    m_State = stateType;

    state_obj = getStateObj();
    QString name_2 = state_obj->getName();

    qDebug() << name_1 << " --> " << name_2;
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

IAttacking::IAttacking(IHero* heroObj):
    IState(heroObj)
{
}

IHitting::IHitting(IHero* heroObj):
    IState(heroObj)
{
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
    // TODO: set timer to quit attacking
    // or fps?

    // TODO: change the state of weapon to attacking

    m_HeroObj->h_startAttack();
    m_HeroObj->setState(HEROSTATE::NORMAL_ATTACKING);
    m_elapsedTime = 0;
}

void CNormalHold::beHit(int damage, QString element)
{
    // Electro Flame Ice
    if ((element == "Ice") && (m_HeroObj->h_getIceResistance() == false))
    {
        m_HeroObj->h_reduceHp(damage);
        m_HeroObj->h_clearKeyPress();
        m_HeroObj->h_startFrozen();
        m_HeroObj->setState(HEROSTATE::ICE_HITTING);
        m_elapsedTime = 0;
    }
    else // Normal
    {
        m_HeroObj->h_reduceHp(damage);
        m_HeroObj->h_startHitting();
        m_HeroObj->setState(HEROSTATE::NORMAL_HITTING);
        m_elapsedTime = 0;
    }
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
    m_elapsedTime += deltaTime;

    // TODO: 时间到了切换武器状态回
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->h_stopAttack();
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
    m_elapsedTime += deltaTime;

    // TODO: 时间到了切换打击状态回
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->h_stopHitting();
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
    m_elapsedTime += deltaTime;

    // TODO: 时间到了切换打击状态回
    if (m_elapsedTime > m_5kMs)
    {
        m_HeroObj->h_stopFrozen();
        m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
        m_elapsedTime = 0;
    }
}

void CIceHitting::key_press(QKeyEvent *event)
{}

void CIceHitting::beHit(int damage, QString element)
{
    if (m_elapsedTime > m_500Ms)
    {
        m_HeroObj->h_reduceHp(damage * 2);
        m_HeroObj->h_stopFrozen();
        m_HeroObj->h_startHitting();
        m_HeroObj->setState(HEROSTATE::NORMAL_HITTING);
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

}
