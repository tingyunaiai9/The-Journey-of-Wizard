//
// Created by gerw on 8/20/24.
//

#include "Armor.h"

Armor::Armor(QGraphicsItem *parent, const QString &pixmapPath) : Item(parent, pixmapPath) {

}

void Armor::mountToParent() {
    Mountable::mountToParent();
    setScale(1);
    setPos(-16, 0);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 0);
    }
}

void Armor::unmount() {
    Mountable::unmount();
    setScale(6);
    if (pixmapItem != nullptr) {
        pixmapItem->setPos(0, 5);
    }
}
