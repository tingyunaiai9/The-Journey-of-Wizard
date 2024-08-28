#include "Weapon.h"

void Weapon::unequip() {
    equipped = false;
}

bool Weapon::isEquipped() const {
    return equipped;
}

void Weapon::equipToParent() {
    equipped = true;
}

void Weapon::startAttack() {
    m_isAttacking = true;
}

void Weapon::stopAttack() {
    m_isAttacking = false;
}

bool Weapon::isAttacking() const {
    return m_isAttacking;
}
