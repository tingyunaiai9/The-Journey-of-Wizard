#include "HeadEquipment.h"

HeadEquipment::HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath) :
    Item(parent, pixmapPath)
{
}

void HeadEquipment::mountToParent() {
    Mountable::mountToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void HeadEquipment::unmount() {
    Mountable::unmount();
    setScale(4);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 20);
    }
}
