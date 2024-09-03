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
    ELECTRO_HITTING
};

class IHero;

class IState: public QObject
{
public:
    explicit IState(IHero* heroObj);

protected:
    IHero* m_HeroObj;

    // TODO: change the time of attack and hit
    qint64 m_500Ms = 500; // the duration of hitting
    qint64 m_5kMs = 5000; // the duration of ice
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
    // TODO: add processFps for flame hold to 受到持续伤害
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
    // TODO: add processFps for electro hold to 受到持续伤害
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

#endif //QT_PROGRAMMING_2024_IHERO_H
