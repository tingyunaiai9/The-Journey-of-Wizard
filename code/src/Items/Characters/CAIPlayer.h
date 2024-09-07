#ifndef QT_PROGRAMMING_2024_CAIPLAYER_H
#define QT_PROGRAMMING_2024_CAIPLAYER_H

#include "Character.h"
#include "Link.h"

#include <QMap>
#include <QObject>

enum AISTATE
{
    FIND_WEAPON
};

class IAIState;

class CAIPlayer : public CPlayer2
{
private:
    AISTATE m_AIState;
    QMap<AISTATE, IAIState*> m_AIStateMap;

public:
    explicit CAIPlayer(QGraphicsItem *parent = nullptr);

    void processAI(Character* opponent);

    // movement
    void clearMoveKeyPress();

    // pick
    void clearPickKeyPress();

    // attack
    void clearAttackKeyPress();

private:
    // AI state
    void initAIState(AISTATE AIStateType);
    void addAIState(AISTATE AIStateType, IAIState* AIStateObj);
    void clearAIStateMap();

    void setAIState(AISTATE AIStateType);

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

private:
    virtual void processMove(QPointF opponentPos);
    virtual void processPick();
    virtual void processAttack();
    virtual void changeState(int opponentHp);
};

class CFindWeapon: public IAIState
{
public:
    explicit CFindWeapon(CAIPlayer* AIPlayerObj) : IAIState(AIPlayerObj) {}

    QString getName() override {return "FindWeapon";}
};

#endif //QT_PROGRAMMING_2024_CAIPLAYER_H
