#ifndef QT_PROGRAMMING_2024_IHERO_H
#define QT_PROGRAMMING_2024_IHERO_H

#include <QObject>
#include <QMap>
#include <QString>

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

    qint64 m_500Ms = 500; // the duration of hitting
    qint64 m_2kMs = 2000; // the duration of ice
    qint64 m_5kMs = 5000; // the duration of flame
    qint64 m_elapsedTime = 0; // the time elapsed since the start of hitting

public:
    virtual QString getName() {return "";};

    virtual bool isAttacking() {return false;};
    virtual bool isHitting() {return false;};

    virtual void setAttack() {};
    virtual void beHit(int damage, QString element) {};

    virtual void processFps(qint64 deltaTime) {};
};

// only beHit while holding
// only start attack while holding
class IHold : public IState
{
public:
    explicit IHold(IHero* heroObj);

    void setAttack() override;
    void beHit(int damage, QString element) override;
};

class IAttacking : public IState
{
public:
    explicit IAttacking(IHero* heroObj);

    bool isAttacking() override;

    virtual void processFps(qint64 deltaTime) override;
};

class IHitting : public IState
{

public:
    explicit IHitting(IHero* heroObj);

    bool isHitting() override;

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

    virtual void h_startAttack() {}; // implement in Character
    virtual void h_stopAttack() {};
    virtual void h_startHitting() {}; // implement in Character
    virtual void h_stopHitting() {};
    virtual void h_reduceHp(int damage) {};
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
};

class CIceHold : public IHold
{
public:
    explicit CIceHold(IHero* heroObj);

    virtual QString getName() override;
};

class CElectroHold : public IHold
{
public:
    explicit CElectroHold(IHero* heroObj);

    virtual QString getName() override;
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
