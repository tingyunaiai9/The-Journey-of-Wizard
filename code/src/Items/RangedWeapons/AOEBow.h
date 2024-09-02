#ifndef QT_PROGRAMMING_2024_AOEBOW_H
#define QT_PROGRAMMING_2024_AOEBOW_H

#include "Bow.h"

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

class WoodenAOEBow : public AOEBow
{
public:
    explicit WoodenAOEBow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }
};

class MetalAOEBow : public AOEBow
{
public:
    explicit MetalAOEBow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }
};

#endif //QT_PROGRAMMING_2024_AOEBOW_H
