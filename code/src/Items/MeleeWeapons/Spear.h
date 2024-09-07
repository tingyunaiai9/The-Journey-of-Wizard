#ifndef QT_PROGRAMMING_2024_SPEAR_H
#define QT_PROGRAMMING_2024_SPEAR_H

#include "MeleeWeapon.h"
#include "../IWood.h"
#include "../IMetal.h"

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
    explicit WoodenSpear(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }
};

class MetalSpear : public Spear, public CMetal
{
public:
    explicit MetalSpear(QGraphicsItem *parent, const QString &pixmapPath);
    ~MetalSpear();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual const QString getName() {return "MetalSpear";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

class NormalWoodenSpear : public WoodenSpear
{
public:
    explicit NormalWoodenSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameWoodenSpear : public WoodenSpear
{
public:
    explicit FlameWoodenSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceWoodenSpear : public WoodenSpear
{
public:
    explicit IceWoodenSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroWoodenSpear : public WoodenSpear
{
public:
    explicit ElectroWoodenSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

class NormalMetalSpear : public MetalSpear
{
public:
    explicit NormalMetalSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameMetalSpear : public MetalSpear
{
public:
    explicit FlameMetalSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceMetalSpear : public MetalSpear
{
public:
    explicit IceMetalSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroMetalSpear : public MetalSpear
{
public:
    explicit ElectroMetalSpear(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_SPEAR_H
