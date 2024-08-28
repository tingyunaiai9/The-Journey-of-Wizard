#ifndef QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
#define QT_PROGRAMMING_2024_ONEHANDEDSWORD_H

#include "MeleeWeapon.h"

class OneHandedSword : public MeleeWeapon
{
public:
    explicit OneHandedSword(QGraphicsItem *parent, const QString &pixmapPath);

    void equipToParent() override;

    void startAttack() override;
    void stopAttack() override;
};

class WoodenOneHandedSword : public OneHandedSword
{
public:
    explicit WoodenOneHandedSword(QGraphicsItem *parent);
};

class MetalOneHandedSword : public OneHandedSword
{
public:
    explicit MetalOneHandedSword(QGraphicsItem *parent);
};

#endif //QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
