#include "BattleScene.h"

#include "../Items/CItemFactory.h"
#include "../Items/Characters/Link.h"

#include "../Items/Maps/Battlefield.h"
#include "../Items/Maps/WoodPlatform.h"
#include "../Items/Maps/RockPlatform.h"
#include "../Items/Maps/MetalPlatform.h"

#include <QDebug>
#include <QInputDialog>
#include <QGraphicsTextItem>
#include <QFont>
#include <QColor>


#define DROPEQUIPMENT
#define DROPARROW

BattleScene::BattleScene(QObject *parent) : Scene(parent)
{
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);

    // init maps
    m_battlefield = new Battlefield();
    m_battlefield->scaleToFitScene(this);
    m_maps.append(m_battlefield);

    WoodPlatform* plat1 = new WoodPlatform();
    // connect(plat1, &IWood::burnOut, this, &BattleScene::burnoutWoodPlatform);
    m_maps.append(plat1);

    WoodPlatform* plat2 = new WoodPlatform();
    // connect(plat2, &IWood::burnOut, this, &BattleScene::burnoutWoodPlatform);
    m_maps.append(plat2);
    plat2->setPos(plat1->pos().x() + 127, 440);  // set the pos of right wooden plarform

    m_maps.append(new RockPlatform());

    MetalPlatform* plat3 = new MetalPlatform();
    m_maps.append(plat3);

    for (Map* map : m_maps)
    {
        addItem(map);
    }

    // init lifebar
    m_bar1 = new QProgressBar();
    m_bar1->setTextVisible(true);
    m_bar1->setRange(0, 100);
    m_bar1->setStyleSheet(
        "QProgressBar {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // white border 2px
        "    border-radius: 5px;"        // border radius 5px
        "    text-align: center;"
        "    color: rgba(255, 255, 255, 200);" // Set text color
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}"
        );

    m_bar2 = new QProgressBar();
    m_bar2->setTextVisible(true);
    m_bar2->setRange(0, 100);
    m_bar2->setInvertedAppearance(true);
    m_bar2->setStyleSheet(
        "QProgressBar {"
        "    background-color: transparent;"
        "    border: 2px solid white;" // white border 2px
        "    border-radius: 5px;" // border radius 5px
        "    text-align: center;"
        "    color: rgba(255, 255, 255, 200);" // Set text color
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}"
    );

    QGraphicsProxyWidget *proxy = nullptr;
    proxy = addWidget(m_bar1);
    proxy->setPos(100, 80);
    proxy->resize(300, 20);
    proxy = addWidget(m_bar2);
    proxy->setPos(880, 80); // position
    proxy->resize(300, 20);

#ifdef DROPEQUIPMENT
    // generate equipment
    equipmentDropTimer = new QTimer(this);
    connect(equipmentDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomEquipment);
    equipmentDropTimer->start(10000); // 10s

    // generate weapon
    weaponDropTimer = new QTimer(this);
    connect(weaponDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomWeapon);
    weaponDropTimer->start(10000); // 10s
#endif

#ifdef DROPARROW
    // generate arrow
    arrowDropTimer = new QTimer(this);
    connect(arrowDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomArrow);
    arrowDropTimer->start(1000); // 1s
#endif
}

void BattleScene::initBattleScene()
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

void BattleScene::processInput()
{
    if (m_player1 != nullptr)
    {
        m_player1->processInput();
    }

    if (m_player2 != nullptr)
    {
        m_player2->processInput();
    }
}

void BattleScene::keyPressEvent(QKeyEvent *event)
{
    bool ok;
    QString cheatCode;
    switch (event->key())
    {
        case Qt::Key_Return:
            cheatCode = QInputDialog::getText(nullptr, "message dialog", "cheat code: ", QLineEdit::Normal, "", &ok);
            if (ok && !cheatCode.isEmpty())
            {
                // cheat code
                QStringList cheatList = cheatCode.split(' ');
                QString weaponCode;
                qreal weaponX;
                if (cheatList.size() > 1)
                {
                    weaponCode = cheatList.at(0);
                    weaponX = static_cast<qreal>(cheatList.at(1).toInt());
                }
                else
                {
                    weaponCode = cheatList.at(0);
                    int maxX = static_cast<int>(this->sceneRect().width());
                    weaponX = static_cast<qreal>(rand() % maxX);
                }
                generateItem(weaponCode, weaponX);
            }
            break;
        case Qt::Key_BracketLeft:
            debugItem(true);
            break;
        case Qt::Key_BracketRight:
            debugItem(false);
            break;
        default:
            break;
    }

    // player
    if (m_player1 != nullptr)
    {
        m_player1->key_press(event);
    }

    if (m_player2 != nullptr)
    {
        m_player2->key_press(event);
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent *event)
{
    // player
    if (m_player1 != nullptr)
    {
        m_player1->key_release(event);
    }

    if (m_player2 != nullptr)
    {
        m_player2->key_release(event);
    }
}

void BattleScene::update()
{
    Scene::update();

    processInput();
    processMovement();
    processPicking();

    processShooting(); // shoot before attack

    processAttacking();
    processAttackingElement();

    // add for hero handle fps by self
    processFps(deltaTime);

    processHp();
}


// move
void BattleScene::processMovement()
{
    if (m_player1 != nullptr)
    {
        // avoid drop out of the scene
        m_player1->move(deltaTime);

        // onground and not jumping
        if (isOnGround(m_player1) && m_player1->getVelocity().y() >= 0)
        {
            m_player1->setAcceleration(QPointF(m_player1->getAcceleration().x(), 0));
            m_player1->setVelocity(QPointF(m_player1->getVelocity().x(), 0));
            m_player1->setPos(m_player1->pos().x(), findNearestMap(m_player1->pos())->getFloorHeight());
            m_player1->setOnGround(true);
        }
        else
        {
            m_player1->setAcceleration(QPointF(m_player1->getAcceleration().x(), Item::GRAVITY.y()));
            m_player1->setOnGround(false);
        }
    }

    if (m_player2 != nullptr)
    {
        m_player2->move(deltaTime);

        // onground and not jumping
        if (isOnGround(m_player2) && m_player2->getVelocity().y() >= 0)
        {
            m_player2->setAcceleration(QPointF(m_player2->getAcceleration().x(), 0));
            m_player2->setVelocity(QPointF(m_player2->getVelocity().x(), 0));
            m_player2->setPos(m_player2->pos().x(), findNearestMap(m_player2->pos())->getFloorHeight());
            m_player2->setOnGround(true);
        }
        else
        {
            m_player2->setAcceleration(QPointF(m_player2->getAcceleration().x(), Item::GRAVITY.y()));
            m_player2->setOnGround(false);
        }
    }

    for(auto equipment : m_spareEquipments)
    {
        equipment->move(deltaTime);

        Map *nearestMap = findNearestMap(equipment->getCenterPos());
        if (isOnMapGround(equipment, nearestMap))
        {
            equipment->setAcceleration(QPointF(equipment->getAcceleration().x(), 0));
            equipment->setVelocity(QPointF(equipment->getVelocity().x(), 0));
            equipment->setPos(equipment->pos().x(), nearestMap->getFloorHeight());
        }
        else
        {
            equipment->setAcceleration(QPointF(equipment->getAcceleration().x(), Item::GRAVITY.y()));
        }
    }

    for(auto weapon : m_spareWeapons)
    {
        weapon->move(deltaTime);

        Map *nearestMap = findNearestMap(weapon->getCenterPos());
        if (isOnMapGround(weapon, nearestMap))
        {
            weapon->setAcceleration(QPointF(weapon->getAcceleration().x(), 0));
            weapon->setVelocity(QPointF(weapon->getVelocity().x(), 0));
            weapon->setPos(weapon->pos().x(), nearestMap->getFloorHeight());
        }
        else
        {
            weapon->setAcceleration(QPointF(weapon->getAcceleration().x(), Item::GRAVITY.y()));
        }
    }
}

Map *BattleScene::findNearestMap(const QPointF &pos)
{
    Map *nearest = nullptr;
    qreal minDistance = std::numeric_limits<qreal>::max();

    for (Map *map : m_maps)
    {
        // Check if the player is within the horizontal bounds of the map
        if ((pos.x() >= map->getAreaRect().left() - 5) &&
            (pos.x() <= map->getAreaRect().right() + 5))
        {
            // positive distance means the player is above the floor of map
            qreal distance = map->getFloorHeight() - pos.y();
            // >= a negative value allows the player to be slightly below the floor
            if ((distance >= -20) && (distance < minDistance))
            {
                minDistance = distance;
                nearest = map;
            }
        }
    }

    return nearest;
}

bool BattleScene::isOnGround(Item *item)
{
    Map *nearestMap = findNearestMap(item->getCenterPos());
    return isOnMapGround(item, nearestMap);
}

bool BattleScene::isOnMapGround(Item *item, Map *nearestMap)
{
    if (nearestMap != nullptr)
    {
        return item->getCenterPos().y() >= nearestMap->getFloorHeight();
    }
    return false;
}

// pick
void BattleScene::processPicking()
{
    if (m_player1 != nullptr)
    {
        if (m_player1->isPicking())
        {
            auto mountable = findNearestUnmountedMountable(m_player1->pos(), 100.);
            if (mountable != nullptr)
            {
                pickupMountable(m_player1, mountable);
            }

            auto weapon = findNearestUnequipWeapon(m_player1->pos(), 100.);
            if (weapon != nullptr)
            {
                pickupWeapon(m_player1, weapon);
            }
        }
    }

    if (m_player2 != nullptr)
    {
        if (m_player2->isPicking())
        {
            auto mountable = findNearestUnmountedMountable(m_player2->pos(), 100.);
            if (mountable != nullptr)
            {
                pickupMountable(m_player2, mountable);
            }

            auto weapon = findNearestUnequipWeapon(m_player2->pos(), 100.);
            if (weapon != nullptr)
            {
                pickupWeapon(m_player2, weapon);
            }
        }
    }
}

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold)
{
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (auto equipment : m_spareEquipments)
    {
        qreal distance = QLineF(pos, equipment->pos()).length();
        if (distance < minDistance)
        {
            minDistance = distance;
            nearest = equipment;
        }
    }

    return nearest;
}

Mountable* BattleScene::pickupMountable(Character* player, Mountable* mountable)
{
    Mountable* previousMountable = nullptr;

    if (auto armor = dynamic_cast<Armor*>(mountable))
    {
        previousMountable = player->pickupArmor(armor);
    }
    else if (auto headEquipment = dynamic_cast<HeadEquipment*>(mountable))
    {
        previousMountable = player->pickupHeadEquipment(headEquipment);
    }
    else if (auto legEquipment = dynamic_cast<LegEquipment*>(mountable))
    {
        previousMountable = player->pickupLegEquipment(legEquipment);
    }

    // remove the mountable picked up from m_spareEquipments
    if (mountable)
    {
        removeFromSpareEquipments(mountable);
    }

    // add the previous mountable to m_spareEquipments
    if (previousMountable)
    {
        addToSpareEquipments(previousMountable);
    }

    return previousMountable;
}

Weapon *BattleScene::findNearestUnequipWeapon(const QPointF &pos, qreal distance_threshold)
{
    Weapon *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (auto weapon : m_spareWeapons)
    {
        qreal distance = QLineF(pos, weapon->pos()).length();
        if (distance < minDistance)
        {
            minDistance = distance;
            nearest = weapon;
        }
    }

    return nearest;
}

Weapon *BattleScene::pickupWeapon(Character *player, Weapon *weapon)
{
    Weapon *previousWeapon = nullptr;

    if (auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon))
    {
        // can not pick if already have one
        auto oldMeleeWeapon = player->getMeleeWeapon();
        if (oldMeleeWeapon != nullptr)
        {
            return nullptr;
        }

        previousWeapon = player->pickupMeleeWeapon(meleeWeapon);
    }
    else if (auto rangedWeapon = dynamic_cast<RangedWeapon *>(weapon))
    {
        // bow: change
        // arrow: store
        previousWeapon = player->pickupRangedWeapon(rangedWeapon);
    }

    if (weapon)
    {
        removeFromSpareWeapons(weapon);
    }

    if (previousWeapon)
    {
        addToSpareWeapons(previousWeapon);
    }

    return previousWeapon;
}

// drop item
void BattleScene::generateRandomEquipment()
{
    Mountable *newEquipment = CEquipmentFactory::getNewRandomEquipment();

    if (newEquipment)
    {
        // generate at a random x position
        qreal randomX = static_cast<qreal>(rand() % static_cast<int>(this->sceneRect().width()));
        newEquipment->setPos(randomX, 0);  // top: y=0
        newEquipment->unmount();
        addItem(newEquipment);

        addToSpareEquipments(newEquipment); // store the equipment
    }
}

void BattleScene::generateRandomWeapon()
{
    Weapon *newWeapon = CWeaponFactory::getNewRandomWeapon();

    if (newWeapon)
    {
        qreal randomX = static_cast<qreal>(rand() % static_cast<int>(this->sceneRect().width()));
        newWeapon->setPos(randomX, 0);  // top: y=0
        newWeapon->unequip();
        addItem(newWeapon);

        addToSpareWeapons(newWeapon);
    }
}

void BattleScene::generateRandomArrow()
{
    Weapon *newArrow = CWeaponFactory::getNewRandomArrow();

    if (newArrow)
    {
        qreal randomX = static_cast<qreal>(rand() % static_cast<int>(this->sceneRect().width()));
        newArrow->setPos(randomX, 0);  // top: y=0
        newArrow->unequip();
        addItem(newArrow);

        addToSpareWeapons(newArrow);
    }
}

void BattleScene::generateItem(QString itemCode, qreal randomX)
{
    Item *newItem = CItemFactory::NewItem(itemCode);

    if (newItem)
    {
        newItem->setPos(randomX, 0);  // top: y=0
        addItem(newItem);

        auto weapon = dynamic_cast<Weapon *>(newItem);
        if (weapon)
        {
            weapon->unequip();
            addToSpareWeapons(weapon);
        }

        auto armor = dynamic_cast<Mountable *>(newItem);
        if (armor)
        {
            armor->unmount();
            addToSpareEquipments(armor);
        }
    }
}

void BattleScene::addToSpareEquipments(Mountable* equipment)
{
    m_spareEquipments.append(equipment);

    // add a timer to remove the equipment
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, equipment]() {
        if (m_spareEquipments.contains(equipment))
        {
            removeItem(equipment);  // remove from scene
            m_spareEquipments.removeOne(equipment);  // remove from spare equipments
            m_spareEquipmentTimers.remove(equipment);  // remove timer
            delete equipment;
        }
    });

    timer->setSingleShot(true);  // only once
    timer->start(10000);  // 10s

    // map timer to equipment
    m_spareEquipmentTimers.insert(equipment, timer);
}

void BattleScene::removeFromSpareEquipments(Mountable* equipment)
{
    m_spareEquipments.removeOne(equipment);

    // if there is a timer for the equipment, remove it
    if (m_spareEquipmentTimers.contains(equipment))
    {
        QTimer* timer = m_spareEquipmentTimers.take(equipment);
        if (timer)
        {
            timer->stop();
            delete timer;
        }
    }
}

void BattleScene::addToSpareWeapons(Weapon *weapon)
{
    m_spareWeapons.append(weapon);

    // add a timer to remove the weapon
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, weapon]() {
        if (m_spareWeapons.contains(weapon))
        {
            removeItem(weapon);  // remove from scene
            m_spareWeapons.removeOne(weapon);  // remove from spare weapons
            m_spareWeaponTimers.remove(weapon);  // remove timer
            delete weapon;
        }
    });

    timer->setSingleShot(true);  // only once
    timer->start(10000);  // 10s

    // map timer to weapon
    m_spareWeaponTimers.insert(weapon, timer);
}

void BattleScene::removeFromSpareWeapons(Weapon *weapon)
{
    m_spareWeapons.removeOne(weapon);

    // if there is a timer for the weapon, remove it
    if (m_spareWeaponTimers.contains(weapon))
    {
        QTimer *timer = m_spareWeaponTimers.take(weapon);
        if (timer)
        {
            timer->stop();
            delete timer;
        }
    }
}

// attack
void BattleScene::processAttacking()
{
    if (m_player1 != nullptr)
    {
        if (m_player1->isAttacking())
        {
            Weapon* weapon = m_player1->getHoldingWeapon();
            auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon);

            if (meleeWeapon)
            {
                // calculate the attack rectangle according to the player's position
                QRectF attackRange = meleeWeapon->getMeleeAttackRange(m_player1);

                QPointF player2Pos = m_player2->pos();

                // the rectangle contains the point?
                if (attackRange.contains(player2Pos))
                {
                    m_player2->beHit(meleeWeapon->getDamage(), meleeWeapon->getElement());
                }
            }
        }
    }

    if (m_player2 != nullptr)
    {
        if (m_player2->isAttacking())
        {
            Weapon* weapon = m_player2->getHoldingWeapon();
            auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon);

            if (meleeWeapon)
            {
                // calculate the attack rectangle according to the player's position
                QRectF attackRange = meleeWeapon->getMeleeAttackRange(m_player2);

                QPointF player1Pos = m_player1->pos();

                // the rectangle contains the point?
                if (attackRange.contains(player1Pos))
                {
                    m_player1->beHit(meleeWeapon->getDamage(), meleeWeapon->getElement());
                }
            }
        }
    }
}

// shoot
void BattleScene::addToShootingWeapons(Weapon *weapon)
{
    weapon->setVisible(true);
    m_shootingWeapons.append(weapon);
}

void BattleScene::removeFromShootingWeapons(Weapon *weapon)
{
    m_shootingWeapons.removeOne(weapon);
}

void BattleScene::processPlayerShooting(Character * player)
{
    if (player->isShooting())
    {
        // shoot ranged weapon
        // bow first to avoid shoot melee weapon and change to bow and shoot bow the same time
        auto bow = dynamic_cast<Bow *>(player->getHoldingWeapon());
        if (bow) // bow shoot
        {
            int shootArrowCount = bow->getShootArrowCount();
            QList<QPointF> shootAttowVelocities = bow->getShootArrowVelocities();

            // check if player has enough arrows
            int totalArrowsAvailable = player->getTotalArrowCount();
            int arrowsToShoot = qMin(shootArrowCount, totalArrowsAvailable);

            if (arrowsToShoot <= 0) // no arrows to shoot
            {
                return;
            }

            QString currentElement = player->getCurrentArrowElement();
            QList<Arrow*> arrowsToFire;

            // use current element arrows first
            QList<Arrow*> currentElementArrows = player->getArrowListByElement(currentElement);
            for (int i = 0; i < currentElementArrows.size() && arrowsToFire.size() < arrowsToShoot; i++)
            {
                arrowsToFire.append(currentElementArrows.at(i));
            }

            // if not enough, use other element arrows
            while(arrowsToFire.size() < arrowsToShoot)
            {
                player->selectNextArrowElement();
                currentElement = player->getCurrentArrowElement();
                currentElementArrows = player->getArrowListByElement(currentElement);
                for (int i = 0; i < currentElementArrows.size() && arrowsToFire.size() < arrowsToShoot; i++)
                {
                    arrowsToFire.append(currentElementArrows.at(i));
                }
            }

            // shoot arrows with different velocities
            for (int i = 0; i < arrowsToFire.size(); ++i)
            {
                Arrow* arrow = arrowsToFire.at(i);
                QPointF velocity = shootAttowVelocities.at(i);
                player->removeArrow(arrow);
                addToShootingWeapons(arrow);
                arrow->shoot(player->isFacingRight(), velocity);
            }

            player->selectNextArrowElement();
        }

        // shoot melee weapon
        auto meleeWeapon = dynamic_cast<MeleeWeapon *>(player->getHoldingWeapon());
        if (meleeWeapon)
        {
            meleeWeapon = dynamic_cast<MeleeWeapon *>(player->abandonWeapon());
            player->setHoldingWeapon(player->getBow());
            addToShootingWeapons(meleeWeapon);
            meleeWeapon->shoot(player->isFacingRight());
        }
    }
}

void BattleScene::processShooting()
{
    if (m_player1 != nullptr)
    {
        processPlayerShooting(m_player1);
    }
    if (m_player2 != nullptr)
    {
        processPlayerShooting(m_player2);
    }

    QList<Weapon*> weaponsToRemove; // record weapons to remove

    for (auto weapon : m_shootingWeapons)
    {
        if (weapon == nullptr)
        {
            continue;
        }

        weapon->setPos(weapon->pos().x() + weapon->getVelocity().x() * (double) deltaTime,
                       fmin(480, weapon->pos().y() + weapon->getVelocity().y() * (double) deltaTime));
        weapon->setVelocity(weapon->getVelocity() + weapon->getAcceleration() * (double) deltaTime);

        // detect if attack the player
        QRectF attackRange; // only attack forward
        attackRange = weapon->getShootAttackRange();

        // attack player1 or player2
        if (m_player1 != nullptr)
        {
            QPointF player1Pos = m_player1->pos();
            if (attackRange.contains(player1Pos))
            {
                m_player1->beHit(weapon->getDamage(), weapon->getElement());
                // remove after attack
                if (weapon && weapon->scene() == this)
                weaponsToRemove.append(weapon); // record the weapon to remove
                continue;
            }
        }

        if (m_player2 != nullptr)
        {
            QPointF player2Pos = m_player2->pos();
            if (attackRange.contains(player2Pos))
            {
                m_player2->beHit(weapon->getDamage(), weapon->getElement());
                // remove after attack
                if (weapon && weapon->scene() == this)
                weaponsToRemove.append(weapon); // record the weapon to remove
                continue;
            }
        }

        // drop on grouns
        if (isOnGround(weapon))
        {
            // attack and disappear
            weaponsToRemove.append(weapon); // record the weapon to remove
            continue;
        }
        else
        {
            weapon->setAcceleration(QPointF(weapon->getAcceleration().x(), Item::GRAVITY.y()));
        }
    }

    // remove weapons
    for (auto weapon : weaponsToRemove)
    {
        if (weapon && weapon->scene() == this)
        {
            removeFromShootingWeapons(weapon);
            removeItem(weapon);
            delete weapon;
            weapon = nullptr;
        }
    }
}

// fps
void BattleScene::processFps(qint64 deltaTime)
{
    if (m_player1 != nullptr)
    {
        m_player1->processFps(deltaTime);
    }

    if (m_player2 != nullptr)
    {
        m_player2->processFps(deltaTime);
    }
}

// update hp
void BattleScene::processHp()
{
    if (m_player1 != nullptr)
    {
        int hp = m_player1->getHp();
        if (hp > 0)
        {
            m_bar1->setValue(hp);
        }
        else
        {
            m_bar1->setValue(0);
            if (m_player1->isHolding())
            {
                m_player1->toDead();

                QTimer::singleShot(5000, [this]() {
                    emit gameOver("Player 2 Wins!");
                });
            }
        }
    }

    if (m_player2 != nullptr)
    {
        int hp = m_player2->getHp();
        if (hp > 0)
        {
            m_bar2->setValue(hp);
        }
        else
        {
            m_bar2->setValue(0);
            if (m_player2->isHolding())
            {
                m_player2->toDead();

                QTimer::singleShot(5000, [this]() {
                    emit gameOver("Player 1 Wins!");
                });
            }
        }
    }
}


void BattleScene::debugItem(bool bDebug)
{
    for (Item *item : m_maps)
    {
        item->showAreaRect(this, bDebug);
    }
    for (Item *item : m_spareEquipments)
    {
        item->showAreaRect(this, bDebug);
    }
    for (Item *item : m_spareWeapons)
    {
        item->showAreaRect(this, bDebug);
    }

    if (m_player1 != nullptr)
    {
        m_player1->showAreaRect(this, bDebug);
    }
    if (m_player2 != nullptr)
    {
        m_player2->showAreaRect(this, bDebug);
    }

    if(!bDebug)
    {
        while (!m_spareWeapons.isEmpty())
        {
            auto item = m_spareWeapons.first();
            removeFromSpareWeapons(item);
            removeItem(item);  // remove from scene
            delete item;
        }
        while (!m_spareEquipments.isEmpty())
        {
            auto item = m_spareEquipments.first();
            removeFromSpareEquipments(item);
            removeItem(item);  // remove from scene
            delete item;
        }
    }
}

// Attack Wood Platform
void BattleScene::processAttackingElement()
{
    if (m_player1 != nullptr)
    {
        if (m_player1->isAttacking())
        {
            Weapon* weapon = m_player1->getHoldingWeapon();
            auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon);
            if (meleeWeapon)
            {
                for (Map *map : m_maps)
                {
                    attackMap(meleeWeapon, map);
                }
            }
        }
    }

    if (m_player2 != nullptr)
    {
        if (m_player2->isAttacking())
        {
            Weapon* weapon = m_player2->getHoldingWeapon();
            auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon);
            if (meleeWeapon)
            {
                for (Map *map : m_maps)
                {
                    attackMap(meleeWeapon, map);
                }
            }
        }
    }

    for (auto weapon : m_shootingWeapons)
    {
        if (weapon == nullptr)
        {
            continue;
        }

        for (Map *map : m_maps)
        {
            attackMap(weapon, map);
        }
    }

    // get list
    QList<QGraphicsItem *> itemsList = items();
    QList<Item *> woodList;
    QList<Item *> metalList;

    for (auto item : itemsList)
    {
        Item * baseItem = dynamic_cast<Item*>(item);
        IWood* woodItem = dynamic_cast<IWood*>(item);
        IMetal* metalItem = dynamic_cast<IMetal*>(item);
        if (woodItem)
        {
            if (baseItem->isOut())
            {
                Map* outMap = dynamic_cast<Map*>(baseItem);
                if (outMap)
                {
                    burnoutWoodPlatform(outMap);
                    continue;
                }

                Weapon* outWeapon = dynamic_cast<Weapon*>(baseItem);
                if (outWeapon)
                {
                    if (outWeapon->isEquipped())
                    {
                        // qDebug() << "remove equipped weapon:" << outWeapon->getName();
                        m_player1->removeWeapon(outWeapon);
                        m_player2->removeWeapon(outWeapon);
                    }
                    else
                    {
                        // qDebug() << "remove idle weapon:" << outWeapon->getName();
                        removeFromSpareWeapons(outWeapon);
                        removeItem(outWeapon);  // remove from scene
                        delete outWeapon;
                    }
                    continue;
                }
            }
            else
            {
                woodList.append(baseItem);
            }
        }
        if (metalItem)
        {
            metalList.append(baseItem);
        }
    }

    // qDebug() << "woodList:";
    for (auto burningItem : woodList)
    {
        if (burningItem->isBurn() == false)
        {
            continue;
        }

        // qDebug() << burningItem->getName();
        for (auto nextItem : woodList)
        {
            if (nextItem == burningItem)
            {
                continue;
            }
            if (nextItem->isBurn() == true)
            {
                continue;
            }

            transHit(burningItem, nextItem, "Flame");
        }

        // player1 and player2
        transHit(burningItem, m_player1, "Flame");
        transHit(burningItem, m_player2, "Flame");
    }

    // qDebug() << "metalList:";
    for (auto shockingItem : metalList)
    {
        if (shockingItem->isShock() == false)
        {
            continue;
        }

        // qDebug() << shockingItem->getName();
        for (auto nextItem : metalList)
        {
            if (nextItem == shockingItem)
            {
                continue;
            }
            if (nextItem->isShock() == true)
            {
                continue;
            }
            transHit(shockingItem, nextItem, "Electro");
        }

        // player1 and player2
        if (m_player1 != nullptr)
        {
            transHit(shockingItem, m_player1, "Electro");
        }
        if (m_player2 != nullptr)
        {
            transHit(shockingItem, m_player2, "Electro");
        }
    }
}

void BattleScene::transHit(Item* srcItem, Item* nextItem, QString element)
{
    QRectF hitRect = srcItem->getAreaRect();
    QRectF nextRect = nextItem->getAreaRect();
    if (hitRect.intersects(nextRect))
    {
        // qDebug() << srcItem->getName() << "-" << element << "->" << nextItem->getName();
        nextItem->beTrans(element, srcItem);
    }
}

void BattleScene::attackMap(Weapon* weapon, Map* map)
{
    QRectF weaponRect = weapon->getAreaRect();
    QRectF platRect = map->getAreaRect();
    if (weaponRect.intersects(platRect))
    {
        map->beHit(weapon->getElement());
    }
}

void BattleScene::burnoutWoodPlatform(Map* map)
{
    if (map)
    {
        m_maps.removeOne(map);
        removeItem(map);
        delete(map);
    }
}

double distanceBetweenRects(const QRectF& rect1, const QRectF& rect2)
{
    // check if two rectangles intersect
    if (rect1.intersects(rect2)) {
        return 0.0;
    }

    // calculate the distance between two rectangles
    double dx = 0.0;
    double dy = 0.0;

    if (rect1.right() < rect2.left())
    {
        dx = rect2.left() - rect1.right();
    }
    else if (rect2.right() < rect1.left())
    {
        dx = rect1.left() - rect2.right();
    }

    if (rect1.bottom() < rect2.top())
    {
        dy = rect2.top() - rect1.bottom();
    }
    else if (rect2.bottom() < rect1.top())
    {
        dy = rect1.top() - rect2.bottom();
    }

    return std::sqrt(dx * dx + dy * dy);
}
