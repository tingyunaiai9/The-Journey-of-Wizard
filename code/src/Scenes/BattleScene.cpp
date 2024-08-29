#include "BattleScene.h"

#include "../Items/CItemFactory.h"

#include "../Items/Characters/Link.h"

#include "../Items/Maps/Battlefield.h"
#include "../Items/Maps/WoodPlatform.h"
#include "../Items/Maps/RockPlatform.h"
#include "../Items/Maps/MetalPlatform.h"

#include "../Items/Armors/BlackWizardRobe.h"
#include "../Items/Armors/FlamebreakerArmor.h"
#include "../Items/Armors/IcebreakerArmor.h"
#include "../Items/Armors/ElectrobreakerArmor.h"

#include "../Items/HeadEquipments/FlamebreakerHat.h"
#include "../Items/HeadEquipments/IcebreakerHat.h"
#include "../Items/HeadEquipments/ElectrobreakerHat.h"

#include "../Items/LegEquipments/FlamebreakerShoes.h"
#include "../Items/LegEquipments/IcebreakerShoes.h"
#include "../Items/LegEquipments/ElectrobreakerShoes.h"

#include <QDebug>

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);

    m_battlefield = new Battlefield();
    m_maps.append(m_battlefield);
    m_maps.append(new WoodPlatform());
    m_maps.append(new WoodPlatform());
    m_maps.last()->setPos(m_maps.at(1)->pos().x() + 128, 440);  // 设置右侧木平台的位置
    m_maps.append(new RockPlatform());
    m_maps.append(new MetalPlatform());

    m_player1 = new CPlayer1();
    m_player2 = new CPlayer2();

    // spareArmor = new FlamebreakerArmor();
    // spareArmor = new IcebreakerArmor();
    // spareArmor = new ElectrobreakerArmor();
    // spareHeadEquipment = new FlamebreakerHat();
    spareHeadEquipment = new IcebreakerHat();
    // spareHeadEquipment = new ElectrobreakerHat();
    // spareLegEquipment = new FlamebreakerShoes();
    // spareLegEquipment = new IcebreakerShoes();
    // spareLegEquipment = new ElectrobreakerShoes();

    for (Map* map : m_maps) {
        addItem(map);
    }

    addItem(m_player1);
    addItem(m_player2);
    // addItem(spareArmor);
    addItem(spareHeadEquipment);
    // addItem(spareLegEquipment);

    m_battlefield->scaleToFitScene(this);
    m_player1->setPos(m_battlefield->getSpawnPos(0.2));
    m_player2->setPos(m_battlefield->getSpawnPos(0.8));

    // spareArmor->unmount();
    // spareArmor->setPos(m_battlefield->getSpawnPos(0.5));
    spareHeadEquipment->unmount();
    spareHeadEquipment->setPos(m_battlefield->getSpawnPos(0.5));
    // spareLegEquipment->unmount();
    // spareLegEquipment->setPos(m_battlefield->getSpawnPos(0.5));


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
        case Qt::Key_K: // attack
            if (m_player1 != nullptr) {
                m_player1->setAttackDown(false);
            }
            break;
        default:
            Scene::keyReleaseEvent(event);
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
        m_player1->setPos(m_player1->pos() +
                          m_player1->getVelocity() * (double) deltaTime);
        m_player1->setVelocity(m_player1->getVelocity() +
                               m_player1->getAcceleration() * (double) deltaTime);

        if (isOnGround(m_player1))
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
}

Map *BattleScene::findNearestMap(const QPointF &pos)
{
    Map *nearest = nullptr;
    qreal minDistance = std::numeric_limits<qreal>::max();

    for (Map *map : m_maps)
    {
        // Check if the player is within the horizontal bounds of the map
        if (pos.x() >= map->sceneBoundingRect().left() - 10 &&
            pos.x() <= map->sceneBoundingRect().right() + 10)
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
            if (picked != nullptr)
            {
                if (auto armor = dynamic_cast<Armor *>(picked))
                {
                    spareArmor = armor;
                }
                else if (auto headEquipment = dynamic_cast<HeadEquipment *>(picked))
                {
                    spareHeadEquipment = headEquipment;
                }
                else if (auto legEquipment = dynamic_cast<LegEquipment *>(picked))
                {
                    spareLegEquipment = legEquipment;
                }
            }
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
        m_spareEquipments.removeOne(mountable);
    }

    // add the previous mountable to m_spareEquipments
    if (previousMountable)
    {
        m_spareEquipments.append(previousMountable);
    }

    return previousMountable;
}

// attack
void BattleScene::processAttacking()
{
    Scene::processAttacking();
    if (m_player1->isAttacking())
    {
        // Attack
    }
}

// drop item
void BattleScene::generateRandomEquipment() {
    QStringList types = {"Armor", "HeadEquipment", "LegEquipment"};
    QStringList elements = {"Flame", "Ice", "Electro"};

    QString type = types.at(rand() % types.size());
    QString element = elements.at(rand() % elements.size());

    Mountable *newEquipment = CEquipmentFactory::NewEquipment(type, element);

    // TODO: set a timer to remove the equipment
    if (newEquipment)
    {
        // generate at a random x position
        qreal randomX = static_cast<qreal>(rand() % static_cast<int>(this->sceneRect().width()));

        newEquipment->setPos(randomX, 0);  // top: y=0

        newEquipment->unmount();
        addItem(newEquipment);
        m_spareEquipments.append(newEquipment); // store the equipment
    }
}
