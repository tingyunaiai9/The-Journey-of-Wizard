#ifndef QT_PROGRAMMING_2024_BATTLESCENE_H
#define QT_PROGRAMMING_2024_BATTLESCENE_H

#include "Scene.h"
#include "../Items/Maps/Map.h"
#include "../Items/Characters/Character.h"
#include "../Items/Mountable.h"
#include "../Items/Weapon.h"

#include <QKeyEvent>
#include <QVector>
#include <QTimer>
#include <QProgressBar>
#include <QGraphicsProxyWidget>

class WoodPlatform;

class BattleScene : public Scene
{
Q_OBJECT

private:
    QVector<Map*> m_maps;
    Map* m_battlefield;

    Character *m_player1;
    Character *m_player2;

    QProgressBar * m_bar1;
    QProgressBar * m_bar2;

    QVector<Mountable*> m_spareEquipments;
    QMap<Mountable*, QTimer*> m_spareEquipmentTimers; // timers for spare equipment to disappear

    QVector<Weapon*> m_spareWeapons;
    QMap<Weapon*, QTimer*> m_spareWeaponTimers; // timers for spare melee weapons to disappear

    QVector<Weapon*> m_shootingWeapons;

    QTimer *equipmentDropTimer; // time to drop equipment
    QTimer *weaponDropTimer; // time to drop weapon
    QTimer *arrowDropTimer; // time to drop arrow

protected slots:
    void update() override;

private slots:
    void generateRandomEquipment();
    void generateRandomWeapon();
    void generateRandomArrow();
    void generateItem(QString itemCode);

public:
    explicit BattleScene(QObject *parent);

    void processInput();
    void processMovement();
    void processPicking();
    void processShooting();
    void processAttacking();
    void processPlayerShooting(Character * player);

    void processFps(qint64 deltaTime);
    void processHp();

    void startSinglePlayerGame();
    void startTwoPlayerGame();
    void startOnlineGame();
    void closeGame();

    void addToSpareWeapons(Weapon* weapon);

    void processAttackingWoodPlatform();
    void burningWoodPlatform(WoodPlatform* plat);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private:

    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());
    Mountable * pickupMountable(Character *player, Mountable *mountable);

    Weapon *findNearestUnequipWeapon(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());
    Weapon *pickupWeapon(Character *player, Weapon *weapon);

    Map *findNearestMap(const QPointF &pos);
    bool isOnGround(Item *item);
    bool isOnMapGround(Item *item, Map *nearestMap);

    void addToSpareEquipments(Mountable* equipment);
    void removeFromSpareEquipments(Mountable* equipment);

    // void addToSpareWeapons(Weapon* weapon);
    void removeFromSpareWeapons(Weapon* weapon);

    void addToShootingWeapons(Weapon* weapon);
    void removeFromShootingWeapons(Weapon* weapon);

public:
    void debugItem(bool bDebug);
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
