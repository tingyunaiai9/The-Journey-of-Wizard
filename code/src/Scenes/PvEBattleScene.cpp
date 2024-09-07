#include "PvEBattleScene.h"

#include <QDebug>

PvEBattleScene::PvEBattleScene(QObject *parent) : BattleScene(parent)
{
    if (m_player2)
    {
        qDebug() << "PvEBattleScene: m_player2 is not nullptr";
    }
}
