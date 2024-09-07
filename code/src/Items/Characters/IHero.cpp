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
    IState* state_obj = nullptr;
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

// burning
void IHero::h_startBurning()
{
    // clear the burning time
    m_burningElapsedTime = 0;
    m_burningIntervalTime = 0;
}

void IHero::processBurningFps(qint64 deltaTime)
{
    m_burningElapsedTime += deltaTime;
    m_burningIntervalTime += deltaTime;

    if (m_burningIntervalTime > m_2kMs && m_burningElapsedTime <= m_10kMs) // flame damage interval
    {
        h_reduceHp(1);
        m_burningIntervalTime = 0;
    }
}

bool IHero::isBurningTimeUp()
{
    return m_burningElapsedTime > m_10kMs;
}

// electric shock
void IHero::h_startElectricShock()
{
    // clear the electric shock time
    m_electricShockElapsedTime = 0;
    m_electricShockIntervalTime = 0;
}

void IHero::processElectricShockFps(qint64 deltaTime)
{
    m_electricShockElapsedTime += deltaTime;
    m_electricShockIntervalTime += deltaTime;

    if (m_electricShockIntervalTime > m_100Ms && m_electricShockElapsedTime <= m_500Ms) // electric damage interval
    {
        h_reduceHp(1);
        m_electricShockIntervalTime = 0;
    }
}

bool IHero::isElectricShockTimeUp()
{
    return m_electricShockElapsedTime > m_500Ms;
}

// IHode, IAttacking, IHitting
IHold::IHold(IHero* heroObj):
    IState(heroObj)
{
}

void IHold::setAttack()
{
    m_HeroObj->h_startAttack();
    m_elapsedTime = 0;
}

void IHold::beHit(int damage, QString element)
{
    m_HeroObj->h_startHitting();
    m_HeroObj->h_reduceHp(damage);
    m_elapsedTime = 0;

    if ((element == "Ice") && (m_HeroObj->h_getIceResistance() == false))
    {
        m_HeroObj->h_clearKeyPress();
        m_HeroObj->h_startFrozen(); // change to frozen
        m_HeroObj->setState(HEROSTATE::ICE_HITTING);
    }
    else if ((element == "Flame") && (m_HeroObj->h_getFlameResistance() == false))
    {
        m_HeroObj->h_startBurning(); // change to burning
        m_HeroObj->setState(HEROSTATE::FLAME_HITTING);
    }
    else if ((element == "Electro") && (m_HeroObj->h_getElectroResistance() == false))
    {
        m_HeroObj->h_startElectricShock(); // change to electric shock
        m_HeroObj->setState(HEROSTATE::ELECTRO_HITTING);
    }
    else // normal or resistance
    {
        m_HeroObj->setState(HEROSTATE::NORMAL_HITTING);
    }
}

IAttacking::IAttacking(IHero* heroObj):
    IState(heroObj)
{
}

void IAttacking::processFps(qint64 deltaTime)
{
    m_elapsedTime += deltaTime;

    // time up, stop attacking
    if (m_elapsedTime > m_200Ms)
    {
        m_HeroObj->h_stopAttack();
    }
}

IHitting::IHitting(IHero* heroObj):
    IState(heroObj)
{
}

void IHitting::processFps(qint64 deltaTime)
{
    m_elapsedTime += deltaTime;

    // time up, stop hitting
    if (m_elapsedTime > m_200Ms)
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

void CFlameHold::setAttack()
{
    IHold::setAttack();
    m_HeroObj->setState(HEROSTATE::FLAME_ATTACKING);
}

void CFlameHold::beHit(int damage, QString element) // flame be hit change to flame hitting
{
    m_HeroObj->h_startHitting();
    m_HeroObj->h_reduceHp(damage);
    m_elapsedTime = 0;

    // TODO: 是否需要再次重新计时？
    // if ((element == "Flame") && (m_HeroObj->h_getFlameResistance() == false))
    // {
    //     m_HeroObj->h_startBurning(); // change to burning
    //     m_HeroObj->setState(HEROSTATE::FLAME_HITTING);
    // }

    // ice hit, change to normal hitting
    if ((element == "Ice") && (m_HeroObj->h_getIceResistance() == false))
    {
        m_HeroObj->h_stopBurning();
        m_HeroObj->setState(HEROSTATE::NORMAL_HITTING);
    }
    else
    {
        m_HeroObj->setState(HEROSTATE::FLAME_HITTING);
    }
}

void CFlameHold::processFps(qint64 deltaTime)
{
    m_HeroObj->processBurningFps(deltaTime);

    if (m_HeroObj->isBurningTimeUp()) // burning time up
    {
        m_HeroObj->h_stopBurning();
        m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
    }
}

CIceHold::CIceHold(IHero* heroObj):
    IHold(heroObj)
{
}

QString CIceHold::getName()
{
    return "IceHold";
}

void CIceHold::setAttack()
{
    // do nothing
}

void CIceHold::beHit(int damage, QString element)
{
    m_HeroObj->h_reduceHp(damage * 2);
    m_HeroObj->h_stopFrozen(); // stop frozen
    m_HeroObj->h_startHitting();
    m_HeroObj->setState(HEROSTATE::NORMAL_HITTING);
    m_elapsedTime = 0;
}

void CIceHold::key_press(QKeyEvent *event)
{
}

void CIceHold::processFps(qint64 deltaTime)
{
    m_elapsedTime += deltaTime;

    if (m_elapsedTime > m_5kMs) // frozen time up
    {
        m_HeroObj->h_stopFrozen();
        m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
        m_elapsedTime = 0;
    }
}

CElectroHold::CElectroHold(IHero* heroObj):
    IHold(heroObj)
{
}

QString CElectroHold::getName()
{
    return "ElectroHold";
}

void CElectroHold::setAttack()
{
    IHold::setAttack();
    m_HeroObj->setState(HEROSTATE::ELECTRO_ATTACKING);
}

void CElectroHold::beHit(int damage, QString element) // electro be hit change to electro hitting
{
    m_HeroObj->h_startHitting();
    m_HeroObj->h_reduceHp(damage);
    m_elapsedTime = 0;

    // TODO: 是否需要再次重新计时？
    // if ((element == "Electro") && (m_HeroObj->h_getElectroResistance() == false))
    // {
    //     m_HeroObj->h_startElectricShock(); // change to electric shock
    //     m_HeroObj->setState(HEROSTATE::ELECTRO_HITTING);
    // }
    m_HeroObj->setState(HEROSTATE::ELECTRO_HITTING);
}

void CElectroHold::processFps(qint64 deltaTime)
{
    m_HeroObj->processElectricShockFps(deltaTime);

    if (m_HeroObj->isElectricShockTimeUp()) // electric shock time up
    {
        m_HeroObj->h_stopElectricShock();
        m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
    }
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

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
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
    m_HeroObj->processBurningFps(deltaTime);

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
    {
        if (m_HeroObj->isBurningTimeUp()) // burning time up, change to normal
        {
            m_HeroObj->h_stopBurning();
            m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
            m_elapsedTime = 0;
        }
        else
        {
            m_HeroObj->setState(HEROSTATE::FLAME_HOLD);
            m_elapsedTime = 0;
        }
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
    // do nothing
    // maybe the state will be never reached
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
    m_HeroObj->processElectricShockFps(deltaTime);

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
    {
        if (m_HeroObj->isElectricShockTimeUp()) // electric shock time up, change to normal
        {
            m_HeroObj->h_stopElectricShock();
            m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
            m_elapsedTime = 0;
        }
        else
        {
            m_HeroObj->setState(HEROSTATE::ELECTRO_HOLD);
            m_elapsedTime = 0;
        }
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

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
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
    m_HeroObj->processBurningFps(deltaTime);

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
    {
        if (m_HeroObj->isBurningTimeUp()) // burning time up, change to normal
        {
            m_HeroObj->h_stopBurning();
            m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
            m_elapsedTime = 0;
        }
        else
        {
            m_HeroObj->setState(HEROSTATE::FLAME_HOLD);
            m_elapsedTime = 0;
        }
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

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
    {
        m_HeroObj->setState(HEROSTATE::ICE_HOLD);
        m_elapsedTime = 0;
    }
}

void CIceHitting::key_press(QKeyEvent *event)
{}

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
    m_HeroObj->processElectricShockFps(deltaTime);

    // time up, change state to hold
    if (m_elapsedTime > m_200Ms)
    {
        if (m_HeroObj->isElectricShockTimeUp()) // electric shock time up, change to normal
        {
            m_HeroObj->h_stopElectricShock();
            m_HeroObj->setState(HEROSTATE::NORMAL_HOLD);
            m_elapsedTime = 0;
        }
        else
        {
            m_HeroObj->setState(HEROSTATE::ELECTRO_HOLD);
            m_elapsedTime = 0;
        }
    }
}

CDead::CDead(IHero* heroObj):
    IState(heroObj)
{
}

QString CDead::getName()
{
    return "Dead";
}

void CDead::key_press(QKeyEvent *event)
{}
