#ifndef QT_PROGRAMMING_2024_MELEEWEAPON_H
#define QT_PROGRAMMING_2024_MELEEWEAPON_H

#include "../Weapon.h"

class MeleeWeapon : public Weapon
{
public:
    explicit MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual int getAttackDistance() const = 0;
    [[nodiscard]] virtual int getDamage() const = 0;

    [[nodiscard]] virtual QString getElement() const = 0;
};

#endif //QT_PROGRAMMING_2024_MELEEWEAPON_H
