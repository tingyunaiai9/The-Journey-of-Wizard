#ifndef QT_PROGRAMMING_2024_MELEEWEAPON_H
#define QT_PROGRAMMING_2024_MELEEWEAPON_H

#include "../Item.h"
#include "../Mountable.h"

class MeleeWeapon : public Item, public Mountable
{
public:
    explicit MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath);

    virtual void equipToParent();
};

#endif //QT_PROGRAMMING_2024_MELEEWEAPON_H
