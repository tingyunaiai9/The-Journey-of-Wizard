#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath) :
    Weapon(parent, pixmapPath)
{
}

int MeleeWeapon::getAttackDistance() const
{
    return m_attackDistance;
}

int MeleeWeapon::getDamage() const
{
    return m_damage;
}

QString MeleeWeapon::getElement() const
{
    return m_element;
}
