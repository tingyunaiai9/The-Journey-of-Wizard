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

class WoodenPrimaryBow : public PrimaryBow
{
public:
    explicit WoodenPrimaryBow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }
};

class MetalPrimaryBow : public PrimaryBow, public CMetal
{
public:
    explicit MetalPrimaryBow(QGraphicsItem *parent = nullptr);
    ~MetalPrimaryBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual const QString getName() {return "MetalPrimaryBow";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

#endif //QT_PROGRAMMING_2024_PRIMARYBOW_H
