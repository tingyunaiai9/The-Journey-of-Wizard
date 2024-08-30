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

    [[nodiscard]] virtual int getAttackDistance() const override { return 100;}
    [[nodiscard]] virtual int getDamage() const override { return 5; }
};

class WoodenOneHandedSword : public OneHandedSword
{
public:
    explicit WoodenOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class MetalOneHandedSword : public OneHandedSword
{
public:
    explicit MetalOneHandedSword(QGraphicsItem *parent = nullptr);

    // TODO: ? Maybe metal to contain different elements
    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

#endif //QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
