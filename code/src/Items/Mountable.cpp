#include "Mountable.h"

Mountable::Mountable(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
}

void Mountable::unmount()
{
    mounted = false;
}

bool Mountable::isMounted() const
{
    return mounted;
}

void Mountable::mountToParent()
{
    mounted = true;
}
