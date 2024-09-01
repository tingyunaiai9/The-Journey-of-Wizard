#include "BattleScene.h"

#include "../Items/CItemFactory.h"

#include "../Items/Characters/Link.h"

#include "../Items/Maps/Battlefield.h"
#include "../Items/Maps/WoodPlatform.h"
#include "../Items/Maps/RockPlatform.h"
#include "../Items/Maps/MetalPlatform.h"

#include "../Items/MeleeWeapons/OneHandedSword.h"
#include "../Items/RangedWeapons/PrimaryBow.h"

#include <QDebug>
#include <QPushButton>
#include <QInputDialog>

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

    for (Map* map : m_maps) {
        addItem(map);
    }

    // init players
    m_player1 = new CPlayer1();
    m_player2 = new CPlayer2();

    addItem(m_player1);
    addItem(m_player2);

    m_battlefield->scaleToFitScene(this);
    m_player1->setPos(m_battlefield->getSpawnPos(0.2));
    m_player2->setPos(m_battlefield->getSpawnPos(0.8));

    // init lifebar
    m_bar1 = new QProgressBar();
    m_bar1->setTextVisible(false);
    m_bar1->setRange(0, 100);
    m_bar1->setStyleSheet(
        "QProgressBar {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // white border 2px
        "    border-radius: 5px;"        // border radius 5px
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}"
        );

    m_bar2 = new QProgressBar();
    m_bar2->setTextVisible(false);
    m_bar2->setRange(0, 100);
    m_bar2->setInvertedAppearance(true);
    // m_bar2->setAttribute(Qt::WA_StaticContents, true);
    m_bar2->setStyleSheet(
        "QProgressBar {"
        "    background-color: transparent;"
        "    border: 2px solid white;"  // white border 2px
        "    border-radius: 5px;"        // border radius 5px
        "}"
        "QProgressBar::chunk {"
        "    background-color: red;"
        "}"
    );

    QGraphicsProxyWidget *proxy = nullptr;
    proxy = addWidget(m_bar1);
    proxy->setPos(100, 100);
    proxy = addWidget(m_bar2);
    proxy->setPos(980, 100); // position

    // TODO: buttons
    // QPushButton *singlePlayerButton = new QPushButton("单人游戏");
    // QPushButton *twoPlayerButton = new QPushButton("双人对战");
    // QPushButton *onlineButton = new QPushButton("联网对战");
    // QPushButton *exitButton = new QPushButton("结束游戏");

    // proxy = addWidget(singlePlayerButton);
    // proxy->setPos(100,50);
    // proxy = addWidget(twoPlayerButton);
    // proxy->setPos(400,50);
    // proxy = addWidget(onlineButton);
    // proxy->setPos(700,50);
    // proxy = addWidget(exitButton);
    // proxy->setPos(1000,50);
    // singlePlayerButton->setFixedSize(200,50);
    // twoPlayerButton->setFixedSize(200,50);
    // onlineButton->setFixedSize(200,50);
    // exitButton->setFixedSize(200,50);

    // connect(singlePlayerButton, &QPushButton::clicked, this, &BattleScene::startSinglePlayerGame);
    // connect(twoPlayerButton, &QPushButton::clicked, this, &BattleScene::startTwoPlayerGame);
    // connect(onlineButton, &QPushButton::clicked, this, &BattleScene::startOnlineGame);
    // connect(exitButton, &QPushButton::clicked, this, &BattleScene::closeGame);

    // // generate equipment
    // equipmentDropTimer = new QTimer(this);
    // connect(equipmentDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomEquipment);
    // equipmentDropTimer->start(10000); // 10s

    // // generate weapon
    // weaponDropTimer = new QTimer(this);
    // connect(weaponDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomWeapon);
    // weaponDropTimer->start(10000);

    // generate arrow
    arrowDropTimer = new QTimer(this);
    connect(arrowDropTimer, &QTimer::timeout, this, &BattleScene::generateRandomArrow);
    arrowDropTimer->start(1000);

    // m_spareWeapon = new NormalWoodenOneHandedSword();
    m_spareWeapon = new MetalPrimaryBow();
    addItem(m_spareWeapon);
    m_spareWeapon->unequip();
    m_spareWeapon->setPos(m_battlefield->getSpawnPos(0.5));
    addToSpareWeapons(m_spareWeapon);
}

void BattleScene::startSinglePlayerGame() {
    // 在这里添加单人游戏的逻辑
    qDebug() << "开始单人游戏";
}

void BattleScene::startTwoPlayerGame() {
    // 在这里添加双人对战的逻辑
    qDebug() << "开始双人对战";
}

void BattleScene::startOnlineGame() {
    // 在这里添加联网对战的逻辑
    qDebug() << "开始联网对战";
}

void BattleScene::closeGame() {
    // 在这里添加联网对战的逻辑
    qDebug() << "结束对战";
}

void BattleScene::processInput() {
    if (m_player1 != nullptr) {
        m_player1->processInput();
    }

    if (m_player2 != nullptr) {
        m_player2->processInput();
    }
}

void BattleScene::keyPressEvent(QKeyEvent *event) {
    bool ok;
    QString text;
    switch (event->key()) {
        case Qt::Key_Return:
            text = QInputDialog::getText(nullptr, "message dialog", "cheat code: ", QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty()) {
                // 处理用户输入的文本
                generateItem(text);
            }
            return Scene::keyPressEvent(event);
        case Qt::Key_BracketLeft:
            debugItem(true);
            return Scene::keyPressEvent(event);
        case Qt::Key_BracketRight:
            debugItem(false);
            return Scene::keyPressEvent(event);
        default:
            Scene::keyPressEvent(event);
            break;
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

    processInput();
    processMovement();
    processPicking();

    processShooting(); // shoot before attack

    processAttacking();

    // add for hero handle fps by self
    processFps(deltaTime);

    processHp();
}


// move
void BattleScene::processMovement() {

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

    if (m_player2 != nullptr)
    {
        m_player2->setPos(m_player2->pos().x() + m_player2->getVelocity().x() * (double) deltaTime,
                          fmin(480, m_player2->pos().y() + m_player2->getVelocity().y() * (double) deltaTime));
        m_player2->setVelocity(m_player2->getVelocity() +
                               m_player2->getAcceleration() * (double) deltaTime);

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

    for(auto weapon : m_spareWeapons)
    {
        // equipment->setPos(equipment->pos() + equipment->getVelocity() * (double) deltaTime);
        weapon->move(deltaTime);

        if (isOnGround(weapon))
        {
            weapon->setAcceleration(QPointF(weapon->getAcceleration().x(), 0));
            weapon->setVelocity(QPointF(weapon->getVelocity().x(), 0));
            weapon->setPos(weapon->pos().x(), findNearestMap(weapon->pos())->getFloorHeight());

            // // 标记武器掉落在地上的位置
            // QGraphicsEllipseItem* weaponPositionMarker = new QGraphicsEllipseItem(weapon->pos().x() - 3, weapon->pos().y() - 3, 6, 6);
            // weaponPositionMarker->setPen(QPen(Qt::red)); // 使用红色标记
            // weaponPositionMarker->setBrush(Qt::red);
            // addItem(weaponPositionMarker);

            // // 可选：在一段时间后自动移除标记
            // QTimer::singleShot(5000, this, [this, weaponPositionMarker]() {
            //     removeItem(weaponPositionMarker);
            //     delete weaponPositionMarker;
            // });
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

Mountable *BattleScene::findNearestUnmountedMountable(const QPointF &pos, qreal distance_threshold) {
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

void BattleScene::generateRandomWeapon() {
    QStringList types = {"OneHandedSword", "TwoHandedSword", "Spear",
                         "PrimaryBow"}; // TODO: add more types
    QStringList elements = {"Normal", "Flame", "Ice", "Electro"};
    QStringList materials = {"Wooden", "Metal"};

    QString type = types.at(rand() % types.size());
    QString element = elements.at(rand() % elements.size());
    QString material = materials.at(rand() % materials.size());

    Weapon *newWeapon = CWeaponFactory::NewWeapon(type, element, material);
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
    QStringList elements = {"Normal", "Flame", "Ice", "Electro"};
    QString element = elements.at(rand() % elements.size());

    Weapon *newArrow = CWeaponFactory::NewWeapon("Arrow", element);
    if (newArrow)
    {
        qreal randomX = static_cast<qreal>(rand() % static_cast<int>(this->sceneRect().width()));
        newArrow->setPos(randomX, 0);  // top: y=0
        newArrow->unequip();
        addItem(newArrow);

        addToSpareWeapons(newArrow);
    }
}

void BattleScene::generateItem(QString itemCode)
{
    Item *newItem = CItemFactory::NewItem(itemCode);

    if (newItem)
    {
        qreal randomX = static_cast<qreal>(rand() % static_cast<int>(this->sceneRect().width()));
        randomX = 727; // for debug
        newItem->setPos(randomX, 0);  // top: y=0
        addItem(newItem);

        auto meleeWeapon = dynamic_cast<MeleeWeapon *>(newItem);
        if (meleeWeapon)
        {
            meleeWeapon->unequip();
            addToSpareWeapons(meleeWeapon);
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
    timer->start(20000);  // 20s

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
                attackRange = QRectF(m_player1->pos().x() - meleeWeapon->getAttackBackwardDistance(),
                                     m_player1->pos().y() - 24,
                                     meleeWeapon->getAttackForwardDistance() + meleeWeapon->getAttackBackwardDistance(),
                                     48);
            }
            else
            {
                attackRange = QRectF(m_player1->pos().x() - meleeWeapon->getAttackForwardDistance(),
                                     m_player1->pos().y() - 24,
                                     meleeWeapon->getAttackForwardDistance() + meleeWeapon->getAttackBackwardDistance(),
                                     48);
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
        // TODO: RangedWeapons
    }

    if (m_player2->isAttacking())
    {
        Weapon* weapon = m_player2->getHoldingWeapon();
        auto meleeWeapon = dynamic_cast<MeleeWeapon *>(weapon);

        if (meleeWeapon)
        {
            bool facingRight = m_player2->isFacingRight();

            // calculate the attack rectangle
            QRectF attackRange;
            if (facingRight)
            {
                attackRange = QRectF(m_player2->pos().x() - meleeWeapon->getAttackBackwardDistance(),
                                     m_player2->pos().y() - 24,
                                     meleeWeapon->getAttackForwardDistance() + meleeWeapon->getAttackBackwardDistance(),
                                     48);
            }
            else
            {
                attackRange = QRectF(m_player2->pos().x() - meleeWeapon->getAttackForwardDistance() - meleeWeapon->getAttackBackwardDistance(),
                                     m_player2->pos().y() - 24,
                                     meleeWeapon->getAttackForwardDistance() + meleeWeapon->getAttackBackwardDistance(),
                                     48);
            }

            QPointF player2Pos = m_player1->pos();

            // 打印矩形的详细信息
            // qDebug() << "Attack Range:" << attackRange;
            // qDebug() << "Player2 Position:" << player2Pos;

            // the rectangle contains the point?
            if (attackRange.contains(player2Pos))
            {
                m_player1->beHit(meleeWeapon->getDamage(), meleeWeapon->getElement());
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
        // TODO: RangedWeapons
    }
}

// shoot
void BattleScene::addToShootingWeapons(Weapon *weapon)
{
    m_shootingWeapons.append(weapon);
}

void BattleScene::removeFromShootingWeapons(Weapon *weapon)
{
    m_shootingWeapons.removeOne(weapon);
}

void BattleScene::processShooting()
{
    if (m_player1->isShooting())
    {
        // shoot melee weapon
        auto meleeWeapon = dynamic_cast<MeleeWeapon *>(m_player1->getHoldingWeapon());
        if (meleeWeapon)
        {
            meleeWeapon = dynamic_cast<MeleeWeapon *>(m_player1->abandonWeapon());
            m_player1->setHoldingWeapon(m_player1->getBow());
            addToShootingWeapons(meleeWeapon);
            meleeWeapon->shoot(m_player1->isFacingRight());
        }

        // shoot ranged weapon
        auto bow = dynamic_cast<Bow *>(m_player1->getHoldingWeapon());
        if (bow)
        {
            // TODO: bow shoot
            int shootArrowCount = bow->getShootArrowCount();
            QList<QPointF> shootAttowVelocities = bow->getShootArrowVelocities();

            // 检查player是否有足够的箭
            // 分别射出每一支箭，对应数组中的速度

        }

    }

    // TODO: move the move part to processMovement
    for (auto weapon : m_shootingWeapons)
    {
        weapon->setPos(weapon->pos().x() + weapon->getVelocity().x() * (double) deltaTime,
                       fmin(480, weapon->pos().y() + weapon->getVelocity().y() * (double) deltaTime));
        weapon->setVelocity(weapon->getVelocity() + weapon->getAcceleration() * (double) deltaTime);

        // detect if attack the player
        QRectF attackRange; // only attack forward

        // TODO: only the shoot weapon player1 shoot
        if (m_player1->isFacingRight())
        {
            attackRange = QRectF(weapon->pos().x() - 55,
                                 weapon->pos().y() - 24 + 60,
                                 weapon->getAttackForwardDistance(),
                                 48 + 50);
        }
        else
        {
            attackRange = QRectF(weapon->pos().x() - weapon->getAttackForwardDistance() + 55,
                                 weapon->pos().y() - 24 + 60,
                                 weapon->getAttackForwardDistance(),
                                 48 + 50);
        }

        // 绘制攻击范围矩形
        // QGraphicsRectItem* attackRangeRect = new QGraphicsRectItem(attackRange);
        // attackRangeRect->setPen(QPen(Qt::red));
        // attackRangeRect->setBrush(Qt::NoBrush);
        // addItem(attackRangeRect);


        // TODO: only attack player2 now
        QPointF player2Pos = m_player2->pos();
        if (attackRange.contains(player2Pos))
        {
            m_player2->beHit(weapon->getDamage(), weapon->getElement());
            // remove after attack
            removeItem(weapon);
            removeFromShootingWeapons(weapon);
            delete weapon;

            continue;
        }

        if (isOnGround(weapon))
        {
            // TODO: attack the map
            // attack and disappear
            removeItem(weapon);
            removeFromShootingWeapons(weapon);
            delete weapon;
        }
        else
        {
            weapon->setAcceleration(QPointF(weapon->getAcceleration().x(), Item::GRAVITY.y()));
        }


        // 调试：绘制射击武器的位置
        // QGraphicsEllipseItem *weaponPositionMarker = new QGraphicsEllipseItem(weapon->pos().x() - 5, weapon->pos().y() - 5, 10, 10);
        // weaponPositionMarker->setPen(QPen(Qt::green));
        // weaponPositionMarker->setBrush(Qt::green);
        // addItem(weaponPositionMarker);

        // 可选：在短时间后自动移除这些标记
        // QTimer::singleShot(100, this, [this, weaponPositionMarker]() {
        //     removeItem(weaponPositionMarker);
        //     delete weaponPositionMarker;
        // });
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

    m_player1->showAreaRect(this, bDebug);
    m_player2->showAreaRect(this, bDebug);
}
