#ifndef QT_PROGRAMMING_2024_PVEBATTLESCENE_H
#define QT_PROGRAMMING_2024_PVEBATTLESCENE_H

#include "BattleScene.h"

class PvEBattleScene : public BattleScene
{
    Q_OBJECT

protected slots:
    void update() override;

public:
    explicit PvEBattleScene(QObject *parent);
    void initBattleScene() override;

    void processAI();
};

#endif //QT_PROGRAMMING_2024_PVEBATTLESCENE_H
