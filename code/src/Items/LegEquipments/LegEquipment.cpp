#include "LegEquipment.h"

LegEquipment::LegEquipment(QGraphicsItem *parent, const QString &pixmapPath) :
    Mountable(parent, pixmapPath)
{
}

void LegEquipment::mountToParent() {
    Mountable::mountToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void LegEquipment::unmount() {
    Mountable::unmount();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 3);
    }
}
