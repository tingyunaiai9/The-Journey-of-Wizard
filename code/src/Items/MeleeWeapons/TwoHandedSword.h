#ifndef QT_PROGRAMMING_2024_TWOHANDEDSWORD_H
#define QT_PROGRAMMING_2024_TWOHANDEDSWORD_H

#include "MeleeWeapon.h"
#include "../IWood.h"
#include "../IMetal.h"

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

class WoodenTwoHandedSword : public TwoHandedSword, public CWood
{
public:
    explicit WoodenTwoHandedSword(QGraphicsItem *parent, const QString &pixmapPath);
    ~WoodenTwoHandedSword();

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }

    virtual const QString getName() override {return "WoodenTwoHandedSword";}

    virtual bool isBurn() override;
    virtual bool isOut() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startBurning() override;
};

class MetalTwoHandedSword : public TwoHandedSword, public CMetal
{
public:
    explicit MetalTwoHandedSword(QGraphicsItem *parent, const QString &pixmapPath);
    ~MetalTwoHandedSword();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual const QString getName() override {return "MetalTwoHandedSword";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

class NormalWoodenTwoHandedSword : public WoodenTwoHandedSword
{
public:
    explicit NormalWoodenTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameWoodenTwoHandedSword : public WoodenTwoHandedSword
{
public:
    explicit FlameWoodenTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceWoodenTwoHandedSword : public WoodenTwoHandedSword
{
public:
    explicit IceWoodenTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroWoodenTwoHandedSword : public WoodenTwoHandedSword
{
public:
    explicit ElectroWoodenTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

class NormalMetalTwoHandedSword : public MetalTwoHandedSword
{
public:
    explicit NormalMetalTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameMetalTwoHandedSword : public MetalTwoHandedSword
{
public:
    explicit FlameMetalTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceMetalTwoHandedSword : public MetalTwoHandedSword
{
public:
    explicit IceMetalTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroMetalTwoHandedSword : public MetalTwoHandedSword
{
public:
    explicit ElectroMetalTwoHandedSword(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_TWOHANDEDSWORD_H
