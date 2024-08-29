#ifndef QT_PROGRAMMING_2024_WEAPON_H
#define QT_PROGRAMMING_2024_WEAPON_H

#include "Item.h"

class Weapon : public Item
{
public:
    Weapon(QGraphicsItem *parent, const QString &pixmapPath);

    virtual void equipToParent();
    virtual void unequip();
    [[nodiscard]] bool isEquipped() const;

    virtual void startAttack();
    virtual void stopAttack();
    [[nodiscard]] bool isAttacking() const;

private:
    bool equipped{};

    bool m_isAttacking{};
};


#endif //QT_PROGRAMMING_2024_WEAPON_H
