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
    explicit WoodenOneHandedSword(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }
};

class MetalOneHandedSword : public OneHandedSword
{
public:
    explicit MetalOneHandedSword(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }
};

class NormalWoodenOneHandedSword : public WoodenOneHandedSword
{
public:
    explicit NormalWoodenOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameWoodenOneHandedSword : public WoodenOneHandedSword
{
public:
    explicit FlameWoodenOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceWoodenOneHandedSword : public WoodenOneHandedSword
{
public:
    explicit IceWoodenOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroWoodenOneHandedSword : public WoodenOneHandedSword
{
public:
    explicit ElectroWoodenOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

class NormalMetalOneHandedSword : public MetalOneHandedSword
{
public:
    explicit NormalMetalOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameMetalOneHandedSword : public MetalOneHandedSword
{
public:
    explicit FlameMetalOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceMetalOneHandedSword : public MetalOneHandedSword
{
public:
    explicit IceMetalOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroMetalOneHandedSword : public MetalOneHandedSword
{
public:
    explicit ElectroMetalOneHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
