#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Armors/Armor.h"
#include "../Items/HeadEquipments/HeadEquipment.h"
#include "../Items/LegEquipments/LegEquipment.h"

#include <QKeyEvent>

class BattleScene : public Scene {
Q_OBJECT

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    void processMovement() override;

    void processPicking() override;

protected slots:

    void update() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());

    static Mountable * pickupMountable(Character *player, Mountable *mountable);

    Map *map;
    Character *m_player1;
    Character *m_player2;

    Armor *spareArmor;
    HeadEquipment *spareHeadEquipment;
    LegEquipment *spareLegEquipment;
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
