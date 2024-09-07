#include "CAIPlayer.h"

#include <QDebug>

CAIPlayer::CAIPlayer(QGraphicsItem *parent) :
    CPlayer2(parent)
{
}

void CAIPlayer::processAI(Character *opponent)
{
    processMove(opponent->pos());
    processPick();
    processAttack();
}

void CAIPlayer::processMove(QPointF opponentPos)
{
    clearMoveKeyPress();

    if (opponentPos.x() < pos().x() - 100) // left
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
        key_press(&keyEvent);
    }
    else if (opponentPos.x() > pos().x() + 100) // right
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
        key_press(&keyEvent);
    }

    if (opponentPos.y() < pos().y() - 100) // up
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
        key_press(&keyEvent);
    }
}

void CAIPlayer::clearMoveKeyPress()
{
    setLeftDown(false);
    setRightDown(false);
    setJumpDown(false);
}

void CAIPlayer::processPick()
{
    clearPickKeyPress();

    int randomNumber = rand() % 100;
    if (randomNumber == 2)
    {
        QKeyEvent keyEvent(QEvent::KeyPress, Qt::Key_Comma, Qt::NoModifier);
        key_press(&keyEvent);
    }
}

void CAIPlayer::clearPickKeyPress()
{
    setPickDown(false);
}

void CAIPlayer::processAttack()
{
}

void CAIPlayer::clearAttackKeyPress()
{
    setAttackDown(false);
    setShootDown(false);
    setSwitchDown(false);
}
