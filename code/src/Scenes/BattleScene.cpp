#include "BattleScene.h"

#include "../Items/CItemFactory.h"

#include "../Items/Characters/Link.h"

#include "../Items/Maps/Battlefield.h"
#include "../Items/Maps/WoodPlatform.h"
#include "../Items/Maps/RockPlatform.h"
#include "../Items/Maps/MetalPlatform.h"

#include <QDebug>

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);

    // init maps
    m_battlefield = new Battlefield();
    m_maps.append(m_battlefield);
    m_maps.append(new WoodPlatform());
    m_maps.append(new WoodPlatform());
    m_maps.last()->setPos(m_maps.at(1)->pos().x() + 128, 440);  // 设置右侧木平台的位置
    m_maps.append(new RockPlatform());
    m_maps.append(new MetalPlatform());

    // init players
    m_player1 = new CPlayer1();
    m_player2 = new CPlayer2();

    for (Map* map : m_maps) {
        addItem(map);
    }

    addItem(m_player1);
    addItem(m_player2);

    m_battlefield->scaleToFitScene(this);
    m_player1->setPos(m_battlefield->getSpawnPos(0.2));
    m_player2->setPos(m_battlefield->getSpawnPos(0.8));

    // init lifebar
    m_bar1 = new QProgressBar();
    m_bar1->setTextVisible(false);
    m_bar1->setRange(0, 100);
    m_bar1->setValue(50);
    m_bar1->setStyleSheet(
        "QProgressBar {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // white border 2px
        "    border-radius: 5px;"        // border radius 5px
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}");

    m_bar2 = new QProgressBar();
    m_bar2->setTextVisible(false);
    m_bar2->setRange(0, 100);
    m_bar2->setValue(80);
    m_bar2->setInvertedAppearance(true);
    m_bar2->setAttribute(Qt::WA_StaticContents, true);
    m_bar2->setStyleSheet(
        "QProgressBar {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // white border 2px
        "    border-radius: 5px;"        // border radius 5px
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}");

    QGraphicsProxyWidget *proxy = nullptr;
    proxy = addWidget(m_bar1);
    proxy->setPos(100, 100);
    proxy = addWidget(m_bar2);
    proxy->setPos(980, 100); // 设置位置

    // generate equipment
    equipmentDropTimer = new QTimer(this);
    connect(equipmentDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomEquipment);
    equipmentDropTimer->start(10000); // 10s
}

void BattleScene::processInput() {
    Scene::processInput();
    if (m_player1 != nullptr) {
        m_player1->processInput();
    }
}

void BattleScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_A:
            if (m_player1 != nullptr) {
                m_player1->setLeftDown(true);
            }
            break;
        case Qt::Key_D:
            if (m_player1 != nullptr) {
                m_player1->setRightDown(true);
            }
            break;
        case Qt::Key_W:
            if (m_player1 != nullptr) {
                m_player1->setJumpDown(true);
            }
            break;
        case Qt::Key_J:
            if (m_player1 != nullptr) {
                m_player1->setPickDown(true);
            }
            break;
        case Qt::Key_K: // attack
            if (m_player1 != nullptr) {
                m_player1->setAttackDown(true);
            }
            break;
        default:
            Scene::keyPressEvent(event);
    }

    //
    if (m_player1 != nullptr) {
        m_player1->key_press(event);
    }

    if (m_player2 != nullptr) {
        m_player2->key_press(event);
    }
}

void BattleScene::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_A:
            if (m_player1 != nullptr) {
                m_player1->setLeftDown(false);
            }
            break;
        case Qt::Key_D:
            if (m_player1 != nullptr) {
                m_player1->setRightDown(false);
            }
            break;
        case Qt::Key_W:
            if (m_player1 != nullptr) {
                m_player1->setJumpDown(false);
            }
            break;
        case Qt::Key_J:
            if (m_player1 != nullptr) {
                m_player1->setPickDown(false);
            }
            break;
        case Qt::Key_K: // release attack
            if (m_player1 != nullptr)
            {
                m_player1->setAttackDown(false);
            }
            break;
        default:
            Scene::keyReleaseEvent(event);
    }

    //
    if (m_player1 != nullptr) {
        m_player1->key_release(event);
    }

    if (m_player2 != nullptr) {
        m_player2->key_release(event);
    }
}

void BattleScene::update() {
    Scene::update();
}


// move
void BattleScene::processMovement() {
    Scene::processMovement();

    if (m_player1 != nullptr)
    {
        // m_player1->setPos(m_player1->pos() +
        //                   m_player1->getVelocity() * (double) deltaTime);
        // avoid drop out of the scene
        m_player1->setPos(m_player1->pos().x() + m_player1->getVelocity().x() * (double) deltaTime,
                          fmin(480, m_player1->pos().y() + m_player1->getVelocity().y() * (double) deltaTime));
        m_player1->setVelocity(m_player1->getVelocity() +
                               m_player1->getAcceleration() * (double) deltaTime);

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

    for(auto equipment : m_spareEquipments)
    {
        // equipment->setPos(equipment->pos() + equipment->getVelocity() * (double) deltaTime);
        equipment->setPos(equipment->pos().x() + equipment->getVelocity().x() * (double) deltaTime,
                          fmin(480, equipment->pos().y() + equipment->getVelocity().y() * (double) deltaTime));
        equipment->setVelocity(equipment->getVelocity() + equipment->getAcceleration() * (double) deltaTime);

        if (isOnGround(equipment))
        {
            equipment->setAcceleration(QPointF(equipment->getAcceleration().x(), 0));
            equipment->setVelocity(QPointF(equipment->getVelocity().x(), 0));
            equipment->setPos(equipment->pos().x(), findNearestMap(equipment->pos())->getFloorHeight());
        }
        else
        {
            equipment->setAcceleration(QPointF(equipment->getAcceleration().x(), Item::GRAVITY.y()));
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
        if (pos.x() >= map->sceneBoundingRect().left() - 5 &&
            pos.x() <= map->sceneBoundingRect().right() + 5)
        {
            // positive distance means the player is above the floor of map
            qreal distance = map->getFloorHeight() - pos.y();
            // >= a negative value allows the player to be slightly below the floor
            if (distance >= -20 && distance < minDistance)
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
    Map *nearestMap = findNearestMap(item->pos());
    if (nearestMap != nullptr)
    {
        return item->pos().y() >= nearestMap->getFloorHeight();
    }
    return false;
}

// pick
void BattleScene::processPicking()
{
    Scene::processPicking();
    if (m_player1->isPicking())
    {
        auto mountable = findNearestUnmountedMountable(m_player1->pos(), 100.);
        if (mountable != nullptr)
        {
            auto picked = pickupMountable(m_player1, mountable);
            // if (picked != nullptr)
            // {
            //     if (auto armor = dynamic_cast<Armor *>(picked))
            //     {
            //         spareArmor = armor;
            //     }
            //     else if (auto headEquipment = dynamic_cast<HeadEquipment *>(picked))
            //     {
            //         spareHeadEquipment = headEquipment;
            //     }
            //     else if (auto legEquipment = dynamic_cast<LegEquipment *>(picked))
            //     {
            //         spareLegEquipment = legEquipment;
            //     }
            // }
        }
    }
}

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items())
    {
        if (auto mountable = dynamic_cast<Mountable *>(item))
        {
            if (!mountable->isMounted())
            {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance)
                {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }

    return nearest;
}

Mountable* BattleScene::pickupMountable(Character* player, Mountable* mountable) {
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

// drop item
void BattleScene::generateRandomEquipment() {
    QStringList types = {"Armor", "HeadEquipment", "LegEquipment"};
    QStringList elements = {"Flame", "Ice", "Electro"};

    QString type = types.at(rand() % types.size());
    QString element = elements.at(rand() % elements.size());

    Mountable *newEquipment = CEquipmentFactory::NewEquipment(type, element);

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
    timer->start(20000);  // 20s

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

// attack
void BattleScene::processAttacking()
{
    Scene::processAttacking();

    if (m_player1->isAttacking())
    {
        Weapon* weapon = m_player1->getHoldingWeapon();
        auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon);
        if (meleeWeapon)
        {
            bool facingRight = m_player1->isFacingRight();

            // calculate the attack rectangle
            QRectF attackRange;
            if (facingRight)
            {
                attackRange = QRectF(m_player1->pos().x(), m_player1->pos().y() - 24, meleeWeapon->getAttackDistance(), 48);
            }
            else
            {
                attackRange = QRectF(m_player1->pos().x() - meleeWeapon->getAttackDistance(), m_player1->pos().y() - 24, meleeWeapon->getAttackDistance(), 48);
            }

            QPointF player2Pos = m_player2->pos();

            // 打印矩形的详细信息
            qDebug() << "Attack Range:" << attackRange;
            qDebug() << "Player2 Position:" << player2Pos;

            // the rectangle contains the point?
            if (attackRange.contains(player2Pos))
            {
                m_player2->beHit(meleeWeapon->getDamage(), meleeWeapon->getElement());
            }

            // 绘制攻击范围矩形
            QGraphicsRectItem* attackRangeRect = new QGraphicsRectItem(attackRange);
            attackRangeRect->setPen(QPen(Qt::red));
            attackRangeRect->setBrush(Qt::NoBrush);
            addItem(attackRangeRect);

            // 绘制 Player2 的位置点
            QGraphicsEllipseItem* player2Point = new QGraphicsEllipseItem(player2Pos.x() - 2, player2Pos.y() - 2, 4, 4);
            player2Point->setPen(QPen(Qt::blue));
            player2Point->setBrush(Qt::blue);
            addItem(player2Point);

            // 可选：在一段时间后自动移除这些绘制内容
            QTimer::singleShot(100, this, [this, attackRangeRect, player2Point]() {
                removeItem(attackRangeRect);
                removeItem(player2Point);
                delete attackRangeRect;
                delete player2Point;
            });
        }
    }
}

// fps
void BattleScene::processFps(qint64 deltaTime)
{
    if (m_player1 != nullptr) {
        m_player1->processFps(deltaTime);
    }

    if (m_player2 != nullptr) {
        m_player2->processFps(deltaTime);
    }
}

// update hp
void BattleScene::processHp()
{
    if (m_player1 != nullptr)
    {
        m_bar1->setValue(m_player1->getHp());
    }

    if (m_player2 != nullptr)
    {
        m_bar2->setValue(m_player2->getHp());
    }
}
