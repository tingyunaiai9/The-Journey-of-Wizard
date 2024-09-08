#ifndef QT_PROGRAMMING_2024_RANGEDWEAPON_H
#define QT_PROGRAMMING_2024_RANGEDWEAPON_H

#include "../Weapon.h"

class RangedWeapon : public Weapon
{
public:
    explicit RangedWeapon(QGraphicsItem *parent, const QString &pixmapPath);
};

#endif //QT_PROGRAMMING_2024_RANGEDWEAPON_H
