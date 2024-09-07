#include "CAIPlayer.h"

#include <QDebug>

CAIPlayer::CAIPlayer(QGraphicsItem *parent) :
    CPlayer2(parent)
{
    // init AI states
    addAIState(FIND_WEAPON, new CFindWeapon(this));
    addAIState(FIND_ARROW, new CFindArrow(this));
    addAIState(MELEE_FIND_OPPONENT, new CMeleeFindOpponent(this));
    addAIState(BOW_FIND_OPPONENT, new CBowFindOpponent(this));
    addAIState(MELEE_ATTACK, new CMeleeAttack(this));
    addAIState(BOW_ATTACK, new CBowAttack(this));
    addAIState(RUN_AWAY, new CRunAway(this));

    initAIState(FIND_WEAPON);
}

void CAIPlayer::processAI(Character *opponent)
{
    IAIState* ai_state_obj = nullptr;
    ai_state_obj = getAIStateObj();

    if (ai_state_obj != nullptr)
    {
        ai_state_obj->processAI(opponent);
    }
}

void CAIPlayer::clearMoveKeyPress()
{
    setLeftDown(false);
    setRightDown(false);
    setJumpDown(false);
}

void CAIPlayer::clearPickKeyPress()
{
    setPickDown(false);
}

void CAIPlayer::clearAttackKeyPress()
{
    setAttackDown(false);
    setShootDown(false);
    setSwitchDown(false);
}

void CAIPlayer::initAIState(AISTATE AIStateType)
{
    m_AIState = AIStateType;
}

void CAIPlayer::addAIState(AISTATE AIStateType, IAIState *AIStateObj)
{
    m_AIStateMap[AIStateType] = AIStateObj;
}

void CAIPlayer::clearAIStateMap()
{
    m_AIStateMap.clear();
}

IAIState *CAIPlayer::getAIStateObj()
{
    return m_AIStateMap[m_AIState];
}

void CAIPlayer::setAIState(AISTATE AIStateType)
{
    IAIState* ai_state_obj = nullptr;
    ai_state_obj = getAIStateObj();
    QString name_1 = ai_state_obj->getName();

    m_AIState = AIStateType;

    ai_state_obj = getAIStateObj();
    QString name_2 = ai_state_obj->getName();

    qDebug() << name_1 << " --> " << name_2;
}

IAIState::IAIState(CAIPlayer *AIPlayerObj) :
    m_AIPlayerObj(AIPlayerObj)
{
}

void IAIState::processAI(Character *opponent)
{
    processMove(opponent->pos());
    processPick();
    processAttack();

    changeState(opponent->getHp());
}

void IAIState::processMove(QPointF opponentPos) // not move
{
}

void IAIState::processPick() // not pick
{
}

void IAIState::processAttack() // not attack
{
}

void IAIState::changeState(int opponentHp)
{
    if (m_AIPlayerObj->getHoldingWeapon() == nullptr)
    {
        m_AIPlayerObj->setAIState(FIND_WEAPON);
    }
}

void CFindWeapon::processMove(QPointF opponentPos) // random move
{
    int randomNumber = rand() % 100;
    if (randomNumber == 99)
    {
        m_AIPlayerObj->clearMoveKeyPress();
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
    else if (randomNumber == 88)
    {
        m_AIPlayerObj->clearMoveKeyPress();
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
    else if (randomNumber == 66)
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
}

void CFindWeapon::processPick() // pick quickly
{
    m_AIPlayerObj->clearPickKeyPress();

    int randomNumber = rand() % 20;
    if (randomNumber == 2)
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Comma, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
}

void CFindWeapon::changeState(int opponentHp)
{
    if (m_AIPlayerObj->getHp() < 20 && m_AIPlayerObj->getHp() < opponentHp)
    {
        m_AIPlayerObj->setAIState(RUN_AWAY);
        return;
    }

    if (m_AIPlayerObj->getHoldingWeapon() == nullptr)
    {
        return;
    }

    if (m_AIPlayerObj->getHoldingWeapon() == m_AIPlayerObj->getMeleeWeapon())
    {
        m_AIPlayerObj->setAIState(MELEE_FIND_OPPONENT);
        return;
    }
    else if (m_AIPlayerObj->getHoldingWeapon() == m_AIPlayerObj->getBow())
    {
        m_AIPlayerObj->setAIState(FIND_ARROW);
        return;
    }
}

void CMeleeFindOpponent::processMove(QPointF opponentPos)
{
    m_AIPlayerObj->clearMoveKeyPress();

    if (opponentPos.x() < m_AIPlayerObj->pos().x() - 70) // left
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
    else if (opponentPos.x() > m_AIPlayerObj->pos().x() + 70) // right
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }

    if (opponentPos.y() < m_AIPlayerObj->pos().y() - 100) // up
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
}

void CBowFindOpponent::processMove(QPointF opponentPos)
{
    m_AIPlayerObj->clearMoveKeyPress();

    if (opponentPos.x() < m_AIPlayerObj->pos().x() - 200) // left
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
    else if (opponentPos.x() > m_AIPlayerObj->pos().x() + 200) // right
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }

    if (opponentPos.y() < m_AIPlayerObj->pos().y() - 100) // up
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
}
