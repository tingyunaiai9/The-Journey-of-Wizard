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

public:
    virtual QString GetName();

    virtual bool isAttacking();
    virtual bool isHitting();

    virtual void setAttack();
    virtual void beHit(int damage, QString element);
};

class IHold : public IState
{
public:
    explicit IHold(IHero* heroObj);
};

class IAttacking : public IState
{
public:
    explicit IAttacking(IHero* heroObj);

    bool isAttacking() override;
};

class IHitting : public IState
{
public:
    explicit IHitting(IHero* heroObj);

    bool isHitting() override;
};

class IHero{
private:
    HEROSTATE m_State;
    QMap<HEROSTATE, IState*> m_StateMap;
protected:
    void InitState(HEROSTATE stateType);
    void AddState(HEROSTATE stateType, IState* stateObj);

    IState* GetStateObj();
    void ClearStateMap();

public:
    void SetState(HEROSTATE stateType);
};


class CNormalHold : public IHold
{
public:
    explicit CNormalHold(IHero* heroObj);

    void setAttack() override;
};

class CFlameHold : public IHold
{
public:
    explicit CFlameHold(IHero* heroObj);
};

class CIceHold : public IHold
{
public:
    explicit CIceHold(IHero* heroObj);
};

class CElectroHold : public IHold
{
public:
    explicit CElectroHold(IHero* heroObj);
};

class CNormalAttacking : public IAttacking
{
public:
    explicit CNormalAttacking(IHero* heroObj);
};

class CFlameAttacking : public IAttacking
{
public:
    explicit CFlameAttacking(IHero* heroObj);
};

class CIceAttacking : public IAttacking
{
public:
    explicit CIceAttacking(IHero* heroObj);
};

class CElectroAttacking : public IAttacking
{
public:
    explicit CElectroAttacking(IHero* heroObj);
};

class CNormalHitting : public IHitting
{
public:
    explicit CNormalHitting(IHero* heroObj);
};

class CFlameHitting : public IHitting
{
public:
    explicit CFlameHitting(IHero* heroObj);;
};

class CIceHitting : public IHitting
{
public:
    explicit CIceHitting(IHero* heroObj);
};

class CElectroHitting : public IHitting
{
public:
    explicit CElectroHitting(IHero* heroObj);
};

#endif //QT_PROGRAMMING_2024_IHERO_H
