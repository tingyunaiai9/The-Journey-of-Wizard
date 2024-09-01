#ifndef QT_PROGRAMMING_2024_ARROW_H
#define QT_PROGRAMMING_2024_ARROW_H

#include "RangedWeapon.h"

class Arrow : public RangedWeapon
{
public:
    explicit Arrow(QGraphicsItem *parent, const QString &pixmapPath);
};

class NormalArrow : public Arrow
{
public:
    explicit NormalArrow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Normal"; }
};

class FlameArrow : public Arrow
{
public:
    explicit FlameArrow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Flame"; }
};

class IceArrow : public Arrow
{
public:
    explicit IceArrow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Ice"; }
};

class ElectroArrow : public Arrow
{
public:
    explicit ElectroArrow(QGraphicsItem *parent = nullptr);

    [[nodiscard]] virtual QString getElement() const override { return "Electro"; }
};

#endif //QT_PROGRAMMING_2024_ARROW_H