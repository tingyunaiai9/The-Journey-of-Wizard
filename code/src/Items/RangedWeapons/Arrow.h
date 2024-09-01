#ifndef QT_PROGRAMMING_2024_ARROW_H
#define QT_PROGRAMMING_2024_ARROW_H

#include "RangedWeapon.h"

class Arrow : public RangedWeapon
{
public:
    explicit Arrow(QGraphicsItem *parent, const QString &pixmapPath);
};

#endif //QT_PROGRAMMING_2024_ARROW_H
