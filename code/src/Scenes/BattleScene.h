#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Armors/Armor.h"
#include "../Items/HeadEquipments/HeadEquipment.h"
#include "../Items/LegEquipments/LegEquipment.h"

#include <QKeyEvent>
#include <QVector>
#include <QTimer>

class BattleScene : public Scene
{
Q_OBJECT

private:
    QVector<Map*> m_maps;
    Map* m_battlefield;

    Character *m_player1;
    Character *m_player2;

    // Armor *spareArmor;
    // HeadEquipment *spareHeadEquipment;
    // LegEquipment *spareLegEquipment;

    QVector<Mountable*> m_spareEquipments;
    QMap<Mountable*, QTimer*> m_spareEquipmentTimers; // timers for spare equipment to disappear

    QTimer *equipmentDropTimer; // time to drop equipment

protected slots:
    void update() override;

private slots:
    void generateRandomEquipment();

public:
    explicit BattleScene(QObject *parent);

    void processInput() override;

    void processMovement() override;

    void processPicking() override;

    void processAttacking() override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());
    Mountable * pickupMountable(Character *player, Mountable *mountable);

    Map *findNearestMap(const QPointF &pos);
    bool isOnGround(Item *item);

    void addToSpareEquipments(Mountable* equipment);
    void removeFromSpareEquipments(Mountable* equipment);
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
