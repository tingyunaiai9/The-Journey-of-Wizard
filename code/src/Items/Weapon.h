#ifndef QT_PROGRAMMING_2024_WEAPON_H
#define QT_PROGRAMMING_2024_WEAPON_H

#include "Item.h"

class Weapon : public Item
{
private:
    bool equipped{};

    bool m_isAttacking{};

public:
    Weapon(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual QString getMaterial() const {return "";}

    virtual void equipToParent();
    virtual void unequip();
    [[nodiscard]] bool isEquipped() const;

    virtual void startAttack();
    virtual void stopAttack();
    [[nodiscard]] bool isAttacking() const;

    [[nodiscard]] virtual int getAttackForwardDistance() const {return 0;}
    [[nodiscard]] virtual int getAttackBackwardDistance() const {return 0;}
    [[nodiscard]] virtual int getDamage() const {return 0;}

    [[nodiscard]] virtual QString getElement() const {return "";}

    virtual void shoot(bool isFacingRight = true, QPointF velocity = {0, 0});
};


#endif //QT_PROGRAMMING_2024_WEAPON_H
