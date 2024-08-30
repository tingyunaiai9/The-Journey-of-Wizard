#ifndef QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
#define QT_PROGRAMMING_2024_ONEHANDEDSWORD_H

#include "MeleeWeapon.h"

class OneHandedSword : public MeleeWeapon
{
public:
    explicit OneHandedSword(QGraphicsItem *parent, const QString &pixmapPath);

    void equipToParent() override;
    void unequip() override;

    void startAttack() override;
    void stopAttack() override;

    [[nodiscard]] virtual int getAttackForwardDistance() const override { return 100;}
    [[nodiscard]] virtual int getAttackBackwardDistance() const override { return 0; }
    [[nodiscard]] virtual int getDamage() const override { return 5; }
};

class WoodenOneHandedSword : public OneHandedSword
{
public:
    explicit WoodenOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameOneHandedSword : public OneHandedSword
{
public:
    explicit FlameOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceOneHandedSword : public OneHandedSword
{
public:
    explicit IceOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroOneHandedSword : public OneHandedSword
{
public:
    explicit ElectroOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
