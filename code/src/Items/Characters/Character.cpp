#include "Character.h"
#include "../MeleeWeapons/TwoHandedSword.h"

#include <QTransform>
#include <QTimer>

Character::Character(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
//    ellipseItem = new QGraphicsEllipseItem(-5, -5, 10, 10, this);
//    // Optionally, set some properties of the ellipse
//    ellipseItem->setBrush(Qt::green);          // Fill color
//    ellipseItem->setZValue(1);

    // modify the scale of the character
    m_imgScale = 4;
    m_imgOffset = -16;
    setScale(m_imgScale);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(m_imgOffset, 0);
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

bool Character::isPickDown() const {
    return m_pickDown;
}

void Character::setPickDown(bool pickDown) {
    m_pickDown = pickDown;
}

bool Character::isPicking() const {
    return m_picking;
}

void Character::processInput() {
    // y: maintain jump speed
    auto velocity = QPointF(0, getVelocity().y());
    // auto acceleration = QPointF(0, 0);
    const auto moveSpeed = 0.3;
    const auto jumpSpeed = -1.25;

    if (isLeftDown()) {
        velocity.setX(velocity.x() - moveSpeed);
        turnLeft();
    }
    if (isRightDown()) {
        velocity.setX(velocity.x() + moveSpeed);
        turnRight();
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

    // attack button
    if (!m_lastAttackDown && m_attackDown) // first time attackDown
    {
        // MeleeWeapon attack
        MeleeWeapon* meleeWeapon = dynamic_cast<MeleeWeapon*>(m_holdingWeapon);
        if (meleeWeapon)
        {
            TwoHandedSword* twoHandedSword = dynamic_cast<TwoHandedSword*>(meleeWeapon);
            if (twoHandedSword == nullptr)
            {
                setAttack(); // change state to attack
            }
            else // 双手剑按下攻击按键后间隔一段时间才开始攻击
            {
                QTimer::singleShot(twoHandedSword->getDelayTime(), this, &Character::setAttack);
            }
        }

        // Bow change arrow
        Bow* bow = dynamic_cast<Bow*>(m_holdingWeapon);
        if (bow)
        {
            // TODO: change arrow
        }

    }
    m_lastAttackDown = m_attackDown;

    // shoot button
    if (!m_lastShootDown && m_shootDown) // first time shootDown
    {
        if(isHolding()) // only shoot while holding
        {
            m_shooting = true;
            setAttack();
        }
        else
        {
            m_shooting = false;
        }
    }
    else
    {
        m_shooting = false;
    }
    m_lastShootDown = m_shootDown;

    // switch weapon button
    if (!m_lastSwitchDown && m_switchDown) // first time switchDown
    {
        if(isHolding())
        {
            switchWeapon();
        }
    }
    m_lastSwitchDown = m_switchDown;

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

MeleeWeapon *Character::pickupMeleeWeapon(MeleeWeapon *newMeleeWeapon)
{
    // TODO: can not pick if already have one
    // already complete in BattleScene::pickupWeapon

    auto oldMeleeWeapon = m_meleeWeapon;

    if (oldMeleeWeapon != nullptr) {
        oldMeleeWeapon->unequip();
        oldMeleeWeapon->setPos(newMeleeWeapon->pos());
        oldMeleeWeapon->setParentItem(parentItem());
    }

    newMeleeWeapon->setParentItem(this);
    newMeleeWeapon->equipToParent();
    m_meleeWeapon = newMeleeWeapon;
    setHoldingWeapon(m_meleeWeapon); // hold the new weapon
    // m_holdingWeapon = newMeleeWeapon;
    if (oldMeleeWeapon != nullptr)
    {
        oldMeleeWeapon->setVisible(true);
    }
    return oldMeleeWeapon;
}

RangedWeapon *Character::pickupRangedWeapon(RangedWeapon *newRangedWeapon)
{
    // Bow
    Bow* newBow = dynamic_cast<Bow*>(newRangedWeapon);
    if (newBow != nullptr)
    {
        auto oldBow = m_bow;

        if (oldBow != nullptr) {
            oldBow->unequip();
            oldBow->setPos(newBow->pos());
            oldBow->setParentItem(parentItem());
        }

        newBow->setParentItem(this);
        newBow->equipToParent();
        m_bow = newBow;
        setHoldingWeapon(m_bow); // hold the new weapon
        // TODO: bug: pick up new bow and old bow disappear
        // m_holdingWeapon = newBow;
        if (oldBow != nullptr)
        {
            oldBow->setVisible(true);
        }
        return oldBow;
    }

    // Arrow
    Arrow* newArrow = dynamic_cast<Arrow*>(newRangedWeapon);
    if (newArrow != nullptr)
    {
        addArrow(newArrow);
        return nullptr; // no old arrow return
    }

    return nullptr;
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

bool Character::isHolding()
{
    IState* state_obj = nullptr;
    state_obj = getStateObj();

    return state_obj->isHolding();
}

bool Character::isAttacking()
{
    IState* state_obj = nullptr;
    state_obj = getStateObj();

    return state_obj->isAttacking();
}

bool Character::isHitting()
{
    IState* state_obj = nullptr;
    state_obj = getStateObj();

    return state_obj->isHitting();
}

void Character::h_startAttack()
{
    if (m_holdingWeapon)
    {
        m_holdingWeapon->startAttack();
    }
}

void Character::h_stopAttack()
{
    if (m_holdingWeapon)
    {
        m_holdingWeapon->stopAttack();
    }
}

void Character::h_startHitting()
{
    if (headEquipment != nullptr) {
        headEquipment->startHitting();
    }
}

void Character::h_stopHitting()
{
    if (headEquipment != nullptr) {
        headEquipment->stopHitting();
    }
}

Weapon *Character::getHoldingWeapon()
{
    return m_holdingWeapon;
}

MeleeWeapon *Character::getMeleeWeapon()
{
    return m_meleeWeapon;
}

Bow *Character::getBow()
{
    return m_bow;
}

void Character::setHoldingWeapon(Weapon *holdingWeapon)
{
    // hide original weapon
    if (m_holdingWeapon != nullptr)
    {
        m_holdingWeapon->setVisible(false);
    }

    m_holdingWeapon = holdingWeapon;
    if (m_holdingWeapon != nullptr)
    {
        m_holdingWeapon->setVisible(true); // show the new weapon
    }
}

void Character::setMeleeWeapon(MeleeWeapon *meleeWeapon)
{
    m_meleeWeapon = meleeWeapon;
}

void Character::setBow(Bow *bow)
{
    m_bow = bow;
}

// arrow
void Character::addArrow(Arrow* arrow)
{
    QString element = arrow->getElement();
    if (!m_arrows.contains(element))
    {
        m_arrows[element] = QList<Arrow*>();
    }
    m_arrows[element].append(arrow);
}

QList<Arrow*> Character::getArrowListByElement(const QString& element) const
{
    return m_arrows.value(element, QList<Arrow*>());
}

void Character::removeArrow(Arrow* arrow)
{
    QString element = arrow->getElement();
    if (m_arrows.contains(element))
    {
        m_arrows[element].removeAll(arrow);
    }
}

// switch weapon
void Character::switchWeapon()
{
    // switch between melee weapon and bow
    if (m_meleeWeapon != nullptr && m_bow != nullptr)
    {
        if (m_holdingWeapon == m_meleeWeapon)
        {
            setHoldingWeapon(m_bow);  // melee weapon switch to bow
        }
        else
        {
            setHoldingWeapon(m_meleeWeapon);  // bow switch to melee weapon
        }
    }
}

void Character::setSwitchDown(bool switchDown)
{
    m_switchDown = switchDown;
}

// shoot
void Character::setShootDown(bool shootDown)
{
    m_shootDown = shootDown;
}

bool Character::isShooting()
{
    return m_shooting;
}

Weapon *Character::abandonWeapon()
{
    if (m_holdingWeapon == nullptr) {
        return nullptr;
    }

    Weapon *oldWeapon = m_holdingWeapon;
    // setHoldingWeapon(nullptr); // use this will lead to the disappear
    m_holdingWeapon = nullptr; // clear the holding weapon
    if (oldWeapon == m_meleeWeapon)
    {
        m_meleeWeapon = nullptr;
    }
    else if (oldWeapon == m_bow)
    {
        m_bow = nullptr;
    }

    // unequip the weapon
    // oldWeapon->unequip();
    // TODO: not add to spareWeapons?

    oldWeapon->setPos(pos());
    oldWeapon->setParentItem(parentItem());
    oldWeapon->setScale(4);

    return oldWeapon;
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

QRectF Character::getAreaRect()
{
    QRectF itemRect = sceneBoundingRect();
    qreal x = itemRect.x();
    qreal width = itemRect.width();

    if (isFacingRight())
    {
        itemRect.setX(x + m_imgScale * m_imgOffset);
    }
    else
    {
        itemRect.setX(x - m_imgScale * m_imgOffset);
    }

    itemRect.setWidth(width);

    return itemRect;
}

// direction
bool Character::isFacingRight() const
{
    return transform().m11() > 0;
}

void Character::turnLeft()
{
    setTransform(QTransform().scale(-1, 1));
}

void Character::turnRight()
{
    setTransform(QTransform().scale(1, 1));
}


void Character::showAreaRect(Scene* scene, bool bDebug)
{
    Item::showAreaRect(scene, bDebug);

    if (m_meleeWeapon)
    {
        m_meleeWeapon->showAreaRect(scene, bDebug);
    }
}
