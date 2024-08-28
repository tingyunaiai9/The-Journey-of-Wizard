#ifndef QT_PROGRAMMING_2024_MELEEWEAPON_H
#define QT_PROGRAMMING_2024_MELEEWEAPON_H

#include "../Item.h"
#include "../Weapon.h"

class MeleeWeapon : public Item, public Weapon
{
public:
    explicit MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath);
};

#endif //QT_PROGRAMMING_2024_MELEEWEAPON_H
