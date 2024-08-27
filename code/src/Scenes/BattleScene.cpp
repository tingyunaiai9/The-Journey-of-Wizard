#include "BattleScene.h"
#include "../Items/Characters/Link.h"
#include "../Items/Maps/Battlefield.h"

#include "../Items/Armors/BlackWizardRobe.h"
#include "../Items/Armors/FlamebreakerArmor.h"
#include "../Items/Armors/IcebreakerArmor.h"
#include "../Items/Armors/ElectrobreakerArmor.h"

#include <QDebug>

BattleScene::BattleScene(QObject *parent) : Scene(parent) {
    // This is useful if you want the scene to have the exact same dimensions as the view
    setSceneRect(0, 0, 1280, 720);
    map = new Battlefield();
    m_player1 = new CPlayer1();
    m_player2 = new CPlayer2();
    spareArmor = new FlamebreakerArmor();

    addItem(map);
    addItem(m_player1);
    addItem(m_player2);
    addItem(spareArmor);

    map->scaleToFitScene(this);
    m_player1->setPos(map->getSpawnPos(0.25));
    m_player2->setPos(map->getSpawnPos(0.75));
    spareArmor->unmount();
    spareArmor->setPos(sceneRect().left() + (sceneRect().right() - sceneRect().left()) * 0.75, map->getFloorHeight());

    m_player1->setFloorHeight(map->getFloorHeight());
    m_player2->setFloorHeight(map->getFloorHeight());
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
        default:
            Scene::keyReleaseEvent(event);
    }
}

void BattleScene::update() {
    Scene::update();
}

void BattleScene::processMovement() {
    Scene::processMovement();
    if (m_player1 != nullptr) {
        m_player1->setPos(m_player1->pos() +
                          m_player1->getVelocity() * (double) deltaTime);
        m_player1->setVelocity(m_player1->getVelocity() +
                               m_player1->getAcceleration() * (double) deltaTime);
        if (m_player1->isOnGround())
        {
            m_player1->setAcceleration(QPointF(m_player1->getAcceleration().x(), 0));
            m_player1->setVelocity(QPointF(m_player1->getVelocity().x(), 0));
            m_player1->setPos(m_player1->pos().x(), map->getFloorHeight());
        }
    }
}

void BattleScene::processPicking() {
    Scene::processPicking();
    if (m_player1->isPicking()) {
        auto mountable = findNearestUnmountedMountable(m_player1->pos(), 100.);
        if (mountable != nullptr) {
            spareArmor = dynamic_cast<Armor *>(pickupMountable(m_player1, mountable));
        }
    }
}

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
    Mountable *nearest = nullptr;
    qreal minDistance = distance_threshold;

    for (QGraphicsItem *item: items()) {
        if (auto mountable = dynamic_cast<Mountable *>(item)) {
            if (!mountable->isMounted()) {
                qreal distance = QLineF(pos, item->pos()).length();
                if (distance < minDistance) {
                    minDistance = distance;
                    nearest = mountable;
                }
            }
        }
    }

    return nearest;
}

Mountable *BattleScene::pickupMountable(Character *player, Mountable *mountable) {
    // Limitation: currently only supports armor
    if (auto armor = dynamic_cast<Armor *>(mountable)) {
        return player->pickupArmor(armor);
    }
    return nullptr;
}
