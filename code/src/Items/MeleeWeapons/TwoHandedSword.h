#ifndef QT_PROGRAMMING_2024_TWOHANDEDSWORD_H
#define QT_PROGRAMMING_2024_TWOHANDEDSWORD_H

#include "MeleeWeapon.h"

class TwoHandedSword : public MeleeWeapon
{
public:
    explicit TwoHandedSword(QGraphicsItem *parent, const QString &pixmapPath);

    void equipToParent() override;
    void unequip() override;

    void startAttack() override;
    void stopAttack() override;

    [[nodiscard]] virtual int getAttackForwardDistance() const override { return 100;}
    [[nodiscard]] virtual int getAttackBackwardDistance() const override { return 100; }
    [[nodiscard]] virtual int getDamage() const override { return 10; }

    [[nodiscard]] int getDelayTime() const {return 500;} // attack delay 500ms
};

class WoodenTwoHandedSword : public TwoHandedSword
{
public:
    explicit WoodenTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameTwoHandedSword : public TwoHandedSword
{
public:
    explicit FlameTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceTwoHandedSword : public TwoHandedSword
{
public:
    explicit IceTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroTwoHandedSword : public TwoHandedSword
{
public:
    explicit ElectroTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_TWOHANDEDSWORD_H
