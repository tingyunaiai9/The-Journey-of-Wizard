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

class WoodenComboBow : public ComboBow
{
public:
    explicit WoodenComboBow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }
};

class MetalComboBow : public ComboBow, public CMetal
{
public:
    explicit MetalComboBow(QGraphicsItem *parent = nullptr);
    ~MetalComboBow();

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }

    virtual void beHit(QString element) override; // from weapon
    virtual void e_startShocking() override; // from IMetal
};

#endif //QT_PROGRAMMING_2024_COMBOBOW_H
