#include "Weapon.h"
#include "./Characters/Character.h"

Weapon::Weapon(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
}

void Weapon::unequip()
{
    equipped = false;
}

bool Weapon::isEquipped() const
{
    return equipped;
}

void Weapon::equipToParent()
{
    equipped = true;
}

void Weapon::startAttack()
{
    m_isAttacking = true;
}

void Weapon::stopAttack()
{
    m_isAttacking = false;
}

bool Weapon::isAttacking() const
{
    return m_isAttacking;
}

QRectF Weapon::getMeleeAttackRange(Character* player)
{
    if (player == nullptr)
    {
        return QRectF();
    }

    if (player->isFacingRight())
    {
        return QRectF(player->pos().x() - getAttackBackwardDistance(),
                      player->pos().y() - 24,
                      getAttackForwardDistance() + getAttackBackwardDistance(),
                      48);
    }
    else
    {
        return QRectF(player->pos().x() - getAttackForwardDistance(),
                      player->pos().y() - 24,
                      getAttackForwardDistance() + getAttackBackwardDistance(),
                      48);
    }
}

void Weapon::shoot(bool isFacingRight, QPointF velocity)
{
    if (isFacingRight)
    {
        setTransform(QTransform().scale(1, 1));
        m_velocity = velocity;
    }
    else
    {
        setTransform(QTransform().scale(-1, 1)); // different direction
        m_velocity = {-velocity.x(), velocity.y()};
    }
}

QRectF Weapon::getShootAttackRange()
{
    if (isFacingRight())
    {
        return QRectF(pos().x() - 55,
                      pos().y() - 24,
                      getAttackForwardDistance(),
                      48);
    }
    else
    {
        return QRectF(pos().x() - getAttackForwardDistance() + 55,
                      pos().y() - 24,
                      getAttackForwardDistance(),
                      48);
    }
}
