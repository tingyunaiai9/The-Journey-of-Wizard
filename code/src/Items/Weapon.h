#ifndef QT_PROGRAMMING_2024_WEAPON_H
#define QT_PROGRAMMING_2024_WEAPON_H

#include "Item.h"

class Weapon : public Item
{
private:
    bool equipped{};

    bool m_isAttacking{};

    QPointF m_velocity{};
    QPointF m_acceleration{};

public:
    Weapon(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual QString getMaterial() const = 0;

    virtual void equipToParent();
    virtual void unequip();
    [[nodiscard]] bool isEquipped() const;

    virtual void startAttack();
    virtual void stopAttack();
    [[nodiscard]] bool isAttacking() const;

    [[nodiscard]] virtual int getAttackForwardDistance() const = 0;
    [[nodiscard]] virtual int getAttackBackwardDistance() const = 0;
    [[nodiscard]] virtual int getDamage() const = 0;
    [[nodiscard]] virtual QString getElement() const = 0;

    // shoot
    [[nodiscard]] const QPointF &getVelocity() const;
    void setVelocity(const QPointF &velocity);

    [[nodiscard]] const QPointF &getAcceleration() const;
    void setAcceleration(const QPointF &acceleration);

    virtual void shoot(bool isFacingRight = true, QPointF velocity = {0, 0});
};


#endif //QT_PROGRAMMING_2024_WEAPON_H
