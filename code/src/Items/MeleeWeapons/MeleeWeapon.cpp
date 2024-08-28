#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
}

void MeleeWeapon::equipToParent()
{
    Mountable::mountToParent();
}
