#ifndef QT_PROGRAMMING_2024_PVEBATTLESCENE_H
#define QT_PROGRAMMING_2024_PVEBATTLESCENE_H

#include "BattleScene.h"

class PvEBattleScene : public BattleScene
{
    Q_OBJECT

public:
    explicit PvEBattleScene(QObject *parent);
    void initBattleScene() override;
};

#endif //QT_PROGRAMMING_2024_PVEBATTLESCENE_H
