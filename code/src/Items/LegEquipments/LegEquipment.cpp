//
// Created by gerw on 8/20/24.
//

#include "LegEquipment.h"

LegEquipment::LegEquipment(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {
}

void LegEquipment::mountToParent() {
    Mountable::mountToParent();
    setScale(1);
    setPos(-16, 0);
}
