#include "Character.h"

#include <QTransform>

Character::Character(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
//    ellipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
//    // Optionally, set some properties of the ellipse
//    ellipseItem->setBrush(Qt::green);          // Fill color
//    ellipseItem->setZValue(1);

    // modify the scale of the character
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(-16, 0);
    }
}

bool Character::isLeftDown() const {
    return m_leftDown;
}

void Character::setLeftDown(bool leftDown) {
    m_leftDown = leftDown;
}

bool Character::isRightDown() const {
    return m_rightDown;
}

void Character::setRightDown(bool rightDown) {
    m_rightDown = rightDown;
}

bool Character::isJumpDown() const {
    return m_jumpDown;
}

void Character::setJumpDown(bool jumpDown) {
    m_jumpDown = jumpDown;
}

// whether the character is on the ground
bool Character::isOnGround() const
{
    return m_onGround;
}

void Character::setOnGround(bool isOnGround)
{
    m_onGround = isOnGround;
}

const QPointF &Character::getVelocity() const {
    return m_velocity;
}

void Character::setVelocity(const QPointF &velocity) {
    Character::m_velocity = velocity;
}

const QPointF &Character::getAcceleration() const {
    return m_acceleration;
}

bool Character::isPickDown() const {
    return m_pickDown;
}

void Character::setPickDown(bool pickDown) {
    m_pickDown = pickDown;
}

bool Character::isPicking() const {
    return m_picking;
}

bool Character::isAttackDown() const {
    return m_attackDown;
}

void Character::setAttackDown(bool attackDown) {
    m_attackDown = attackDown;
}

bool Character::isAttacking() const {
    return m_attacking;
}


void Character::setAcceleration(const QPointF &acceleration) {
    m_acceleration = acceleration;
}

void Character::processInput() {
    // y: maintain jump speed
    auto velocity = QPointF(0, getVelocity().y());
    // auto acceleration = QPointF(0, 0);
    const auto moveSpeed = 0.3;
    const auto jumpSpeed = -1.25;

    if (isLeftDown()) {
        velocity.setX(velocity.x() - moveSpeed);
        setTransform(QTransform().scale(-1, 1));
    }
    if (isRightDown()) {
        velocity.setX(velocity.x() + moveSpeed);
        setTransform(QTransform().scale(1, 1));
    }
    if (isJumpDown() && isOnGround())
    {
        // velocity.setY(velocity.y() + jumpSpeed);
        velocity.setY(jumpSpeed);
    }
    // else if (!isOnGround())
    // {
    //     acceleration.setY(Item::GRAVITY.y());
    // }
    setVelocity(velocity);
    // setAcceleration(acceleration);

    if (!m_lastPickDown && m_pickDown)
    { // first time pickDown
        m_picking = true;
    }
    else
    {
        m_picking = false;
    }
    m_lastPickDown = m_pickDown;

    if (!m_lastAttackDown && m_attackDown) // first time attackDown
    {
        m_attacking = true;
        m_meleeWeapon->startAttack();
    }
    else if (m_lastAttackDown && !m_attackDown) // last time attackDown, this time not attackDown
    {
        m_attacking = false;
        m_meleeWeapon->stopAttack();
    }
    else
    {
        m_attacking = false;
    }
    m_lastAttackDown = m_attackDown;
}

Armor *Character::pickupArmor(Armor *newArmor) {
    auto oldArmor = armor;
    if (oldArmor != nullptr) {
        oldArmor->unmount();
        oldArmor->setPos(newArmor->pos());
        oldArmor->setParentItem(parentItem());
    }
    newArmor->setParentItem(this);
    newArmor->mountToParent();
    armor = newArmor;
    return oldArmor;
}

HeadEquipment *Character::pickupHeadEquipment(HeadEquipment *newHeadEquipment) {
    auto oldHeadEquipment = headEquipment;
    if (oldHeadEquipment != nullptr) {
        oldHeadEquipment->unmount();
        oldHeadEquipment->setPos(newHeadEquipment->pos());
        oldHeadEquipment->setParentItem(parentItem());
    }
    newHeadEquipment->setParentItem(this);
    newHeadEquipment->mountToParent();
    headEquipment = newHeadEquipment;
    return oldHeadEquipment;
}

LegEquipment *Character::pickupLegEquipment(LegEquipment *newLegEquipment) {
    auto oldLegEquipment = legEquipment;
    if (oldLegEquipment != nullptr) {
        oldLegEquipment->unmount();
        oldLegEquipment->setPos(newLegEquipment->pos());
        oldLegEquipment->setParentItem(parentItem());
    }
    newLegEquipment->setParentItem(this);
    newLegEquipment->mountToParent();
    legEquipment = newLegEquipment;
    return oldLegEquipment;
}
