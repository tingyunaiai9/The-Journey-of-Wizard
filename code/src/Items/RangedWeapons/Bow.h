#ifndef QT_PROGRAMMING_2024_BOW_H
#define QT_PROGRAMMING_2024_BOW_H

#include "RangedWeapon.h"

class Bow : public RangedWeapon
{
public:
    explicit Bow(QGraphicsItem *parent, const QString &pixmapPath);

    void equipToParent() override;
    void unequip() override;

    void startAttack() override;
    void stopAttack() override;

    // get shoot arrow count and velocities
    virtual int getShootArrowCount() const { return 0;}
    virtual QList<QPointF> getShootArrowVelocities() const {return QList<QPointF>();}
};

#endif //QT_PROGRAMMING_2024_BOW_H
