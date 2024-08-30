#ifndef QT_PROGRAMMING_2024_MELEEWEAPON_H
#define QT_PROGRAMMING_2024_MELEEWEAPON_H

#include "../Weapon.h"

class MeleeWeapon : public Weapon
{
protected:
    int m_attackDistance;
    int m_damage;

    QString m_element;

public:
    explicit MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual int getAttackDistance() const;
    [[nodiscard]] virtual int getDamage() const;

    [[nodiscard]] virtual QString getElement() const;
};

#endif //QT_PROGRAMMING_2024_MELEEWEAPON_H
