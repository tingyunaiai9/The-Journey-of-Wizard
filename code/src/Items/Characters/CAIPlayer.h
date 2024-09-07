#ifndef QT_PROGRAMMING_2024_CAIPLAYER_H
#define QT_PROGRAMMING_2024_CAIPLAYER_H

#include "Character.h"
#include "Link.h"

class CAIPlayer : public CPlayer2
{
public:
    explicit CAIPlayer(QGraphicsItem *parent = nullptr);

    void processAI(Character* opponent);

private:
    // movement
    void processMove(QPointF opponentPos);
    void clearMoveKeyPress();

    // pick
    void processPick();
    void clearPickKeyPress();

    // attack
    void processAttack();
    void clearAttackKeyPress();
};

#endif //QT_PROGRAMMING_2024_CAIPLAYER_H
