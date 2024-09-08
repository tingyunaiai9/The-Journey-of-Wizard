#ifndef QT_PROGRAMMING_2024_AOEBOW_H
#define QT_PROGRAMMING_2024_AOEBOW_H

#include "Bow.h"
#include "../IWood.h"
#include "../IMetal.h"

class AOEBow : public Bow
{
public:
    explicit AOEBow(QGraphicsItem *parent, const QString &pixmapPath);

    int getShootArrowCount() const override {return 3;}
    QList<QPointF> getShootArrowVelocities() const override
    {
        return QList<QPointF>{QPointF(2, -0.5), QPointF(2, 0), QPointF(2, 0.5)};
    }
};

class WoodenAOEBow : public AOEBow, public CWood
{
public:
    explicit WoodenAOEBow(QGraphicsItem *parent = nullptr);
    ~WoodenAOEBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }

    virtual const QString getName() override {return "WoodenAOEBow";}

    virtual bool isBurn() override;
    virtual bool isOut() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startBurning() override;
};

class MetalAOEBow : public AOEBow, public CMetal
{
public:
    explicit MetalAOEBow(QGraphicsItem *parent = nullptr);
    ~MetalAOEBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual const QString getName() override {return "MetalAOEBow";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

#endif //QT_PROGRAMMING_2024_AOEBOW_H
