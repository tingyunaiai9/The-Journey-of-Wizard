#ifndef QT_PROGRAMMING_2024_SPEAR_H
#define QT_PROGRAMMING_2024_SPEAR_H

#include "MeleeWeapon.h"

class Spear : public MeleeWeapon
{
public:
    explicit Spear(QGraphicsItem *parent, const QString &pixmapPath);

    void equipToParent() override;
    void unequip() override;

    void startAttack() override;
    void stopAttack() override;

    [[nodiscard]] virtual int getAttackForwardDistance() const override { return 150;}
    [[nodiscard]] virtual int getAttackBackwardDistance() const override { return 0; }
    [[nodiscard]] virtual int getDamage() const override { return 5; }
};

class WoodenSpear : public Spear
{
public:
    explicit WoodenSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameSpear : public Spear
{
public:
    explicit FlameSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceSpear : public Spear
{
public:
    explicit IceSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroSpear : public Spear
{
public:
    explicit ElectroSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_SPEAR_H
