//
// Created by gerw on 8/20/24.
//

#include "HeadEquipment.h"

HeadEquipment::HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {
}

void HeadEquipment::mountToParent() {
    Mountable::mountToParent();
    setScale(1);
    setPos(-16, 0);
}
