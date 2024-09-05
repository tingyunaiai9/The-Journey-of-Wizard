#ifndef QT_PROGRAMMING_2024_IHERO_H
#define QT_PROGRAMMING_2024_IHERO_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QKeyEvent>

enum HEROSTATE
{
    NORMAL_HOLD,
    FLAME_HOLD,
    ICE_HOLD,
    ELECTRO_HOLD,
    NORMAL_ATTACKING,
    FLAME_ATTACKING,
    ICE_ATTACKING,
    ELECTRO_ATTACKING,
    NORMAL_HITTING,
    FLAME_HITTING,
    ICE_HITTING,
    ELECTRO_HITTING,
    DEAD
};

class IHero;

class IState: public QObject
{
public:
    explicit IState(IHero* heroObj);

protected:
    IHero* m_HeroObj;

    qint64 m_200Ms = 200; // the new duration of attack and hitting
    qint64 m_500Ms = 500;
    qint64 m_5kMs = 5000; // the duration of frozen
    qint64 m_10kMs = 10000; // the duration of flame
    qint64 m_elapsedTime = 0; // the time elapsed since the start of hitting

public:
    virtual QString getName() {return "";};

    virtual bool isHolding() {return false;};
    virtual bool isAttacking() {return false;};
    virtual bool isHitting() {return false;};

    virtual void setAttack() {};
    virtual void beHit(int damage, QString element) {};

    virtual void key_press(QKeyEvent *event);
    virtual void key_release(QKeyEvent *event);
    virtual void processFps(qint64 deltaTime) {};
};

// only beHit while holding
// only start attack while holding
class IHold : public IState
{
public:
    explicit IHold(IHero* heroObj);

    bool isHolding() override {return true;}

    virtual void setAttack() override;
    virtual void beHit(int damage, QString element) override;
};

class IAttacking : public IState
{
public:
    explicit IAttacking(IHero* heroObj);

    bool isAttacking() override {return true;}

    virtual void processFps(qint64 deltaTime) override;
};

class IHitting : public IState
{
public:
    explicit IHitting(IHero* heroObj);

    bool isHitting() override {return true;}

    virtual void processFps(qint64 deltaTime) override;
};

class IHero: public QObject
{
private:
    HEROSTATE m_State;
    QMap<HEROSTATE, IState*> m_StateMap;

    qint64 m_100Ms = 100; // the interval of electric damage
    qint64 m_500Ms = 500; // the duration of electric shock
    qint64 m_2kMs = 2000; // the interval of flame damage
    qint64 m_10kMs = 10000; // the duration of flame

    qint64 m_burningElapsedTime = 0; // the time elapsed since the start of burning
    qint64 m_burningIntervalTime = 0; // the time elapsed since the last flame damage
    qint64 m_electricShockElapsedTime = 0; // the time elapsed since the start of electric shock
    qint64 m_electricShockIntervalTime = 0; // the time elapsed since the last electric damage

protected:
    void initState(HEROSTATE stateType);
    void addState(HEROSTATE stateType, IState* stateObj);

    IState* getStateObj();
    void clearStateMap();

public:
    void setState(HEROSTATE stateType);

    // implement in Character
    virtual void h_reduceHp(int damage) {};

    virtual void h_startAttack() {};
    virtual void h_stopAttack() {};
    virtual void h_startHitting() {};
    virtual void h_stopHitting() {};

    virtual bool h_getElectroResistance() {return false;};
    virtual bool h_getFlameResistance() {return false;};
    virtual bool h_getIceResistance() {return false;};

    virtual void h_startFrozen() {};
    virtual void h_stopFrozen() {};
    virtual void h_clearKeyPress() {};

    virtual void h_startBurning();
    virtual void h_stopBurning() {};
    void processBurningFps(qint64 deltaTime);
    bool isBurningTimeUp();

    virtual void h_startElectricShock();
    virtual void h_stopElectricShock() {};
    void processElectricShockFps(qint64 deltaTime);
    virtual bool isElectricShockTimeUp();

    virtual void h_keyPress(QKeyEvent *event) {};
    virtual void h_keyRelease(QKeyEvent *event) {};
};


class CNormalHold : public IHold
{
public:
    explicit CNormalHold(IHero* heroObj);

    virtual QString getName() override;

    void setAttack() override;
};

class CFlameHold : public IHold
{
public:
    explicit CFlameHold(IHero* heroObj);

    virtual QString getName() override;

    void setAttack() override;
    virtual void beHit(int damage, QString element) override;

    void processFps(qint64 deltaTime) override;
};

class CIceHold : public IHold
{
public:
    explicit CIceHold(IHero* heroObj);

    virtual QString getName() override;

    void setAttack() override;
    virtual void beHit(int damage, QString element) override;

    virtual void key_press(QKeyEvent *event) override;
    virtual void processFps(qint64 deltaTime) override;
};

class CElectroHold : public IHold
{
public:
    explicit CElectroHold(IHero* heroObj);

    virtual QString getName() override;

    void setAttack() override;
    virtual void beHit(int damage, QString element) override;

    void processFps(qint64 deltaTime) override;
};

class CNormalAttacking : public IAttacking
{
public:
    explicit CNormalAttacking(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CFlameAttacking : public IAttacking
{
public:
    explicit CFlameAttacking(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CIceAttacking : public IAttacking
{
public:
    explicit CIceAttacking(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CElectroAttacking : public IAttacking
{
public:
    explicit CElectroAttacking(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CNormalHitting : public IHitting
{
public:
    explicit CNormalHitting(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CFlameHitting : public IHitting
{
public:
    explicit CFlameHitting(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CIceHitting : public IHitting
{
public:
    explicit CIceHitting(IHero* heroObj);

    virtual QString getName() override;

    virtual void key_press(QKeyEvent *event) override;
    virtual void processFps(qint64 deltaTime) override;
};

class CElectroHitting : public IHitting
{
public:
    explicit CElectroHitting(IHero* heroObj);

    virtual QString getName() override;

    virtual void processFps(qint64 deltaTime) override;
};

class CDead : public IState
{
public:
    explicit CDead(IHero* heroObj);

    virtual QString getName() override;

    virtual void key_press(QKeyEvent *event) override;
};

#endif //QT_PROGRAMMING_2024_IHERO_H
