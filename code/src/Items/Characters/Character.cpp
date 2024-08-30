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

    // init 12 states
    addState(NORMAL_HOLD, new CNormalHold(this));
    addState(FLAME_HOLD, new CFlameHold(this));
    addState(ICE_HOLD, new CIceHold(this));
    addState(ELECTRO_HOLD, new CElectroHold(this));

    addState(NORMAL_ATTACKING, new CNormalAttacking(this));
    addState(FLAME_ATTACKING, new CFlameAttacking(this));
    addState(ICE_ATTACKING, new CIceAttacking(this));
    addState(ELECTRO_ATTACKING, new CElectroAttacking(this));

    addState(NORMAL_HITTING, new CNormalHitting(this));
    addState(FLAME_HITTING, new CFlameHitting(this));
    addState(ICE_HITTING, new CIceHitting(this));
    addState(ELECTRO_HITTING, new CElectroHitting(this));

    initState(NORMAL_HOLD);
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
    m_velocity = velocity;
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
    setVelocity(velocity);
    // setAcceleration(acceleration);

    if (!m_lastPickDown && m_pickDown) // first time pickDown
    {
        m_picking = true;
    }
    else
    {
        m_picking = false;
    }
    m_lastPickDown = m_pickDown;

    // attack
    if (!m_lastAttackDown && m_attackDown) // first time attackDown
    {
        setAttack(); // change state to attack
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

void Character::key_press(QKeyEvent *event)
{}

void Character::key_release(QKeyEvent *event)
{}

void Character::processFps(qint64 deltaTime)
{
    IState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->processFps(deltaTime);
}


// attack
void Character::setAttackDown(bool attackDown)
{
    m_attackDown = attackDown;
}

void Character::setAttack()
{
    // check whether the character is holding a weapon
    if (m_holdingWeapon == nullptr)
    {
        return;
    }

    IState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->setAttack();
}

bool Character::isAttacking()
{
    IState* state_obj = nullptr;
    state_obj = getStateObj();

    return state_obj->isAttacking();
}

void Character::h_startAttack()
{
    // TODO: check m_holdingWeapon?
    m_holdingWeapon->startAttack();
}

void Character::h_stopAttack()
{
    m_holdingWeapon->stopAttack();
}

// hit
void Character::h_reduceHp(int damage)
{
    m_hp -= damage;
}

int Character::getHp() const
{
    return m_hp;
}

void Character::beHit(int damage, QString element)
{
    IState* state_obj = nullptr;
    state_obj = getStateObj();

    state_obj->beHit(damage, element);
}
