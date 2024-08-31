#include "HeadEquipment.h"

HeadEquipment::HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath) :
    Mountable(parent, pixmapPath)
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

void HeadEquipment::startHitting()
{
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(-1);
    }
}

void HeadEquipment::stopHitting()
{
    if (pixmapItem != nullptr) {
        pixmapItem->setRotation(0);
    }
}
