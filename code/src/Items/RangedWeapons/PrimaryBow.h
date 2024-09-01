#ifndef QT_PROGRAMMING_2024_PRIMARYBOW_H
#define QT_PROGRAMMING_2024_PRIMARYBOW_H

#include "Bow.h"

class PrimaryBow : public Bow
{
public:
    explicit PrimaryBow(QGraphicsItem *parent, const QString &pixmapPath);
};

class WoodenPrimaryBow : public PrimaryBow
{
public:
    explicit WoodenPrimaryBow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getMaterial() const override { return "Wooden"; }
};

class MetalPrimaryBow : public PrimaryBow
{
public:
    explicit MetalPrimaryBow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getMaterial() const override { return "Metal"; }
};

#endif //QT_PROGRAMMING_2024_PRIMARYBOW_H
