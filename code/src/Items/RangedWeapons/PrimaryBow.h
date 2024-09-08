#ifndef QT_PROGRAMMING_2024_PRIMARYBOW_H
#define QT_PROGRAMMING_2024_PRIMARYBOW_H

#include "Bow.h"
#include "../IWood.h"
#include "../IMetal.h"

class PrimaryBow : public Bow
{
public:
    explicit PrimaryBow(QGraphicsItem *parent, const QString &pixmapPath);

    int getShootArrowCount() const override {return 1;}
    QList<QPointF> getShootArrowVelocities() const override
    {
        return QList<QPointF>{QPointF(1.5, 0)};
    }
};

class WoodenPrimaryBow : public PrimaryBow, public CWood
{
public:
    explicit WoodenPrimaryBow(QGraphicsItem *parent = nullptr);
    ~WoodenPrimaryBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }

    virtual const QString getName() override {return "WoodenPrimaryBow";}

    virtual bool isBurn() override;
    virtual bool isOut() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startBurning() override;
};

class MetalPrimaryBow : public PrimaryBow, public CMetal
{
public:
    explicit MetalPrimaryBow(QGraphicsItem *parent = nullptr);
    ~MetalPrimaryBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual const QString getName() override {return "MetalPrimaryBow";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

#endif //QT_PROGRAMMING_2024_PRIMARYBOW_H
