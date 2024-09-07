#include "PvEBattleScene.h"
#include "../Items/Characters/Link.h"

#include <QDebug>

PvEBattleScene::PvEBattleScene(QObject *parent) : BattleScene(parent)
{
}

void PvEBattleScene::initBattleScene()
{
    // init players
    m_player1 = new CPlayer1();
    m_player2 = new CPlayer2();

    addItem(m_player1);
    addItem(m_player2);

    m_player1->setPos(m_battlefield->getSpawnPos(0.2));
    m_player2->setPos(m_battlefield->getSpawnPos(0.8));

    // set battle scene for players
    m_player1->setBattleScene(this);
    m_player2->setBattleScene(this);
}
