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
