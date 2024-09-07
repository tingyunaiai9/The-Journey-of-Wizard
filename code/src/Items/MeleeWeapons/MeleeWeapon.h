#ifndef QT_PROGRAMMING_2024_MELEEWEAPON_H
#define QT_PROGRAMMING_2024_MELEEWEAPON_H

#include "../Weapon.h"

class MeleeWeapon : public Weapon
{
public:
    explicit MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath);

    void shoot(bool isFacingRight = true, QPointF velocity = {1, 0}) override;
    QRectF getShootAttackRange() override;

    virtual const QString getName() override {return "MeleeWeapon";}

    virtual QPointF getCenterPos() override;
    virtual QRectF getAreaRect() override;
};

#endif //QT_PROGRAMMING_2024_MELEEWEAPON_H
