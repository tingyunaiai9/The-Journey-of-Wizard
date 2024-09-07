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

protected:
    QVector<Map*> m_maps;
    Map* m_battlefield;

    Character *m_player1 = nullptr;
    Character *m_player2 = nullptr;

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

protected slots:
    void generateRandomEquipment();
    void generateRandomWeapon();
    void generateRandomArrow();
    void generateItem(QString itemCode, qreal randomX);

signals:
    void gameOver(const QString& winnerText); // signal for game over to main window

public:
    explicit BattleScene(QObject *parent);
    virtual void initBattleScene();

    void processInput();
    void processMovement();
    void processPicking();
    void processShooting();
    void processAttacking();
    void processPlayerShooting(Character * player);

    void processFps(qint64 deltaTime);
    void processHp();

    void addToSpareWeapons(Weapon* weapon);

    void processAttackingElement();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

public:
    Weapon *findNearestUnequipWeapon(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());

protected:
    Mountable *findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold = std::numeric_limits<qreal>::max());
    Mountable * pickupMountable(Character *player, Mountable *mountable);

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

    void attackMap(Weapon* weapon, Map* map);
    void burnoutWoodPlatform(Map* map);

    void transHit(Item* srcItem, Item* nextItem, QString element);

public:
    void debugItem(bool bDebug);
};


#endif //QT_PROGRAMMING_2024_BATTLESCENE_H
