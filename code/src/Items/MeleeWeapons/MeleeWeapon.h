#ifndef QT_PROGRAMMING_2024_MELEEWEAPON_H
#define QT_PROGRAMMING_2024_MELEEWEAPON_H

#include "../Weapon.h"

class MeleeWeapon : public Weapon
{
public:
    explicit MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual int getAttackForwardDistance() const = 0;

    [[nodiscard]] virtual int getAttackBackwardDistance() const = 0;

    [[nodiscard]] virtual int getDamage() const = 0;

    [[nodiscard]] virtual QString getElement() const = 0;

    void shoot(bool isFacingRight = true, QPointF velocity = {1, 0}) override;
};

#endif //QT_PROGRAMMING_2024_MELEEWEAPON_H
