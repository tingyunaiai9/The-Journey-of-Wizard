#ifndef QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
#define QT_PROGRAMMING_2024_ONEHANDEDSWORD_H

#include "MeleeWeapon.h"

class OneHandedSword : public MeleeWeapon
{
protected:
    int m_attackDistance = 50;
    int m_damage = 5;

public:
    explicit OneHandedSword(QGraphicsItem *parent, const QString &pixmapPath);

    void equipToParent() override;

    void startAttack() override;
    void stopAttack() override;
};

class WoodenOneHandedSword : public OneHandedSword
{
protected:
    QString m_element = "Normal";

public:
    explicit WoodenOneHandedSword(QGraphicsItem *parent);
};

class MetalOneHandedSword : public OneHandedSword
{
protected:
    QString m_element = "Normal"; // TODO: ? Maybe metal to contain different elements

public:
    explicit MetalOneHandedSword(QGraphicsItem *parent);
};

#endif //QT_PROGRAMMING_2024_ONEHANDEDSWORD_H
