#ifndef QT_PROGRAMMING_2024_CAIPLAYER_H
#define QT_PROGRAMMING_2024_CAIPLAYER_H

#include "Character.h"
#include "Link.h"

#include <QMap>
#include <QObject>

enum AISTATE
{
    FIND_WEAPON,
    FIND_ARROW,
    MELEE_FIND_OPPONENT,
    BOW_FIND_OPPONENT,
    MELEE_ATTACK,
    BOW_ATTACK,
    RUN_AWAY
};

class IAIState;

class CAIPlayer : public CPlayer2
{
private:
    AISTATE m_AIState;
    QMap<AISTATE, IAIState*> m_AIStateMap;

public:
    explicit CAIPlayer(QGraphicsItem *parent = nullptr);

    void setAIState(AISTATE AIStateType);

    void processAI(Character* opponent);

    // movement
    void clearMoveKeyPress();
    void moveTo(QPointF targetPos);
    void moveRandomly();

    // pick
    void clearPickKeyPress();

    // attack
    void clearAttackKeyPress();

private:
    // AI state
    void initAIState(AISTATE AIStateType);
    void addAIState(AISTATE AIStateType, IAIState* AIStateObj);
    void clearAIStateMap();

    IAIState* getAIStateObj();
};


class IAIState: public QObject
{
protected:
    CAIPlayer* m_AIPlayerObj;

public:
    explicit IAIState(CAIPlayer* AIPlayerObj);

    virtual QString getName() {return "";}

    void processAI(Character* opponent);

    virtual void processMove(QPointF opponentPos);
    virtual void processPick();
    virtual void processAttack();
    virtual void changeState(int opponentHp, QPointF opponentPos);
};

class CFindWeapon: public IAIState
{
public:
    explicit CFindWeapon(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "FindWeapon";}

    void processMove(QPointF opponentPos) override;
    void processPick() override;

    void changeState(int opponentHp, QPointF opponentPos) override;
};

class CFindArrow: public IAIState
{
public:
    explicit CFindArrow(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "FindArrow";}

    void processMove(QPointF opponentPos) override;
    void processPick() override;

    void changeState(int opponentHp, QPointF opponentPos) override;
};

class CMeleeFindOpponent: public IAIState
{
public:
    explicit CMeleeFindOpponent(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "MeleeFindOpponent";}

    void processMove(QPointF opponentPos) override;

    void changeState(int opponentHp, QPointF opponentPos) override;
};

class CBowFindOpponent: public IAIState
{
public:
    explicit CBowFindOpponent(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "BowFindOpponent";}

    void processMove(QPointF opponentPos) override;

    void changeState(int opponentHp, QPointF opponentPos) override;
};

class CMeleeAttack: public IAIState
{
public:
    explicit CMeleeAttack(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "MeleeAttack";}

    void processAttack() override;

    void changeState(int opponentHp, QPointF opponentPos) override;
};

class CBowAttack: public IAIState
{
public:
    explicit CBowAttack(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "BowAttack";}

    void processAttack() override;

    void changeState(int opponentHp, QPointF opponentPos) override;
};

class CRunAway: public IAIState
{
public:
    explicit CRunAway(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "RunAway";}

    void processMove(QPointF opponentPos) override;
};

#endif //QT_PROGRAMMING_2024_CAIPLAYER_H
