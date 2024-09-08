#ifndef QT_PROGRAMMING_2024_COMBOBOW_H
#define QT_PROGRAMMING_2024_COMBOBOW_H

#include "Bow.h"
#include "../IWood.h"
#include "../IMetal.h"

class ComboBow : public Bow
{
public:
    explicit ComboBow(QGraphicsItem *parent, const QString &pixmapPath);

    int getShootArrowCount() const override {return 3;}
    QList<QPointF> getShootArrowVelocities() const override
    {
        return QList<QPointF>{QPointF(2.5, 0), QPointF(2, 0), QPointF(1.5, 0)};
    }
};

class WoodenComboBow : public ComboBow, public CWood
{
public:
    explicit WoodenComboBow(QGraphicsItem *parent = nullptr);
    ~WoodenComboBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }

    virtual const QString getName() override {return "WoodenComboBow";}

    virtual bool isBurn() override;
    virtual bool isOut() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startBurning() override;
};

class MetalComboBow : public ComboBow, public CMetal
{
public:
    explicit MetalComboBow(QGraphicsItem *parent = nullptr);
    ~MetalComboBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual const QString getName() override {return "MetalComboBow";}

    virtual bool isShock() override;
    virtual void beHit(QString element) override;
    virtual void beTrans(QString element, Item* srcItem) override;
    virtual void e_startShocking() override; // from IMetal
};

#endif //QT_PROGRAMMING_2024_COMBOBOW_H
