#include "CAIPlayer.h"

#include <QDebug>

CAIPlayer::CAIPlayer(QGraphicsItem *parent) :
    CPlayer2(parent)
{
    // init AI states
    addAIState(FIND_WEAPON, new CFindWeapon(this));

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

void IAIState::processMove(QPointF opponentPos)
{
    m_AIPlayerObj->clearMoveKeyPress();

    if (opponentPos.x() < m_AIPlayerObj->pos().x() - 100) // left
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
    else if (opponentPos.x() > m_AIPlayerObj->pos().x() + 100) // right
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

void IAIState::processPick()
{
    m_AIPlayerObj->clearPickKeyPress();

    int randomNumber = rand() % 100;
    if (randomNumber == 2)
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Comma, Qt::NoModifier);
        m_AIPlayerObj->key_press(&keyEvent);
    }
}

void IAIState::processAttack()
{
    if (m_AIPlayerObj->getHoldingWeapon() == nullptr)
    {
        return;
    }

    m_AIPlayerObj->clearAttackKeyPress();
    if (m_AIPlayerObj->getHoldingWeapon() == m_AIPlayerObj->getMeleeWeapon()) // melee weapon
    {
        int randomNumber = rand() % 100;
        if (randomNumber == 2)
        {
            QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Period, Qt::NoModifier);
            m_AIPlayerObj->key_press(&keyEvent);
        }
    }
    else if (m_AIPlayerObj->getHoldingWeapon() == m_AIPlayerObj->getBow()) // bow
    {
        int randomNumber = rand() % 100;
        if (randomNumber == 2)
        {
            QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Slash, Qt::NoModifier);
            m_AIPlayerObj->key_press(&keyEvent);
        }
    }
}

void IAIState::changeState(int opponentHp)
{
    // if (m_AIPlayerObj->getHoldingWeapon() == nullptr)
    // {
    //     m_AIPlayerObj->setAIState(FIND_WEAPON);
    // }
}
