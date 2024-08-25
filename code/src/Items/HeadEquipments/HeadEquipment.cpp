//
// Created by gerw on 8/20/24.
//

#include "HeadEquipment.h"

HeadEquipment::HeadEquipment(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {
}

void HeadEquipment::mountToParent() {
    Mountable::mountToParent();
    setScale(0.4);
    setPos(-30, -210);
}
